#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <memory>
#include <vector>
#include <unordered_map>

class Client;
class Service;
class BrokerService;

enum EVENT_ID
{
	SYSTEM_STATUS_CHANGED,

	EVENT_ID_TOTAL
};

class Client
{
public:
	Client() {}
	virtual ~Client() {}

	void OnEventNotified(EVENT_ID id, void* arg)
	{
		switch (id)
		{
			case EVENT_ID::SYSTEM_STATUS_CHANGED:
			{
				int status = *(int*)arg;
				printf("Client received system status: %d\n", status);
				break;
			}
			default:
			{
				break;
			}
		}
	}

private:
	friend class BrokerService;
};

class BrokerService
{
public:
	static BrokerService* GetInstance();
	~BrokerService() {}

	void RegisterEvent(Client* cli, Service* serv, EVENT_ID id)
	{
		manager[serv][id].push_back(cli);
	}

	void NotifyClient(Service* serv, EVENT_ID id, void* arg)
	{
		if (manager.find(serv) == manager.end())
		{
			return;
		}

		std::vector<Client*>& clients = manager[serv][id];
		for (Client* client : clients)
		{
			client->OnEventNotified(id, arg);
		}
	}

private:
	static BrokerService* instance;
	BrokerService() {}

	std::unordered_map<Service*, std::unordered_map<EVENT_ID, std::vector<Client*>>> manager;
};
BrokerService* BrokerService::instance = nullptr;
BrokerService* BrokerService::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new BrokerService();
	}

	return instance;
}

class Service
{
public:
	Service() {}
	virtual ~Service() {}

	void NotifyClient(EVENT_ID id, void* arg)
	{
		BrokerService::GetInstance()->NotifyClient(this, id, arg);
	}

private:
	friend class BrokerService;
};

class System : public Service
{
public:
	System()
		: Service(), status(0)
	{
		printf("System init\n");

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		pthread_t t; 
		pthread_create(&t, &attr, &System::run, this);
	}
	virtual ~System() {}

private:
	static void* run(void* arg)
	{
		printf("%x: %s\n", pthread_self(), __func__);
		System *pSys = (System*)arg;

		while (true)
		{
			pSys->status++;
			pSys->status %= 2;

			pSys->NotifyClient(EVENT_ID::SYSTEM_STATUS_CHANGED, (void*)&pSys->status);

			sleep(1);
		}

		return (void*)0;
	}
private:
	int status; // 0: SUSPENDING 1: RUNNING
};

class Navi : public Client
{
public:
	Navi() {}
	virtual ~Navi() {}

private:

};

int main()
{
	std::shared_ptr<System> sys = std::make_shared<System>();
	Navi navi_app;
	BrokerService::GetInstance()->RegisterEvent(&navi_app, sys.get(), EVENT_ID::SYSTEM_STATUS_CHANGED);

	while (true)
	{

	}

	return 0;
}

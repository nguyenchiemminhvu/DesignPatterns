#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <memory>
#include <queue>

enum REQUEST_ID
{
	GET_SYSTEM_STATUS,

	REQUEST_ID_TOTAL
};

class Client;
struct Request
{
	REQUEST_ID id;
	char buffer[1024];
	Client* client;
};

class Client
{
public:
	
	Client() 
	{
		pthread_mutex_init(&res_lock, nullptr);
	}
	virtual ~Client() {}

	template<typename T>
	T GetResult(Request* req)
	{
		printf("%s\n", __func__);
		T res;
		pthread_mutex_lock(&res_lock);
		memcpy(&res, req->buffer, sizeof(T));
		pthread_mutex_unlock(&res_lock);
		return res;
	}

	void WaitForResult()
	{
		printf("%s\n", __func__);
		pthread_mutex_lock(&res_lock);
	}

	void NotifiedResult()
	{
		printf("%s\n", __func__);
		pthread_mutex_unlock(&res_lock);
	}

private:
	pthread_mutex_t res_lock;
};

class System
{
public:
	System()
		: status(0)
	{
		printf("System init\n");

		pthread_mutex_init(&queue_lock, nullptr);

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		pthread_t t; 
		pthread_create(&t, &attr, &System::run, this);
	}
	virtual ~System() {}

	void add_request(Request* r)
	{
		pthread_mutex_lock(&queue_lock);
		message_queue.push(r);
		r->client->WaitForResult();
		pthread_mutex_unlock(&queue_lock);
	}

private:
	static void* run(void* arg)
	{
		printf("%x: %s\n", pthread_self(), __func__);
		System *pSys = (System*)arg;

		pSys->status = 1;
		while (true)
		{
			if (!pSys->message_queue.empty())
			{
				pthread_mutex_lock(&pSys->queue_lock);

				Request *r = pSys->message_queue.front();
				pSys->message_queue.pop();

				switch (r->id)
				{
					case REQUEST_ID::GET_SYSTEM_STATUS:
					{
						memcpy(r->buffer, &pSys->status, sizeof(int));
					}
					default:
					{
						break;
					}
				}

				r->client->NotifiedResult();
				pthread_mutex_unlock(&pSys->queue_lock);
			}

			sleep(1);
		}

		return (void*)0;
	}
private:
	int status; // 0: SUSPENDING 1: RUNNING

	std::queue<Request*> message_queue;
	pthread_mutex_t queue_lock;
};

class LegacyModule : public Client
{
public:
	LegacyModule(std::shared_ptr<System> sys) 
	{
		pSys = sys;
	}
	virtual ~LegacyModule() {}

	int CheckSystemStatus()
	{
		int status;
		
		Request* r = new Request();
		r->id = REQUEST_ID::GET_SYSTEM_STATUS;
		r->client = this;
		pSys->add_request(r);
		status = this->GetResult<int>(r);
		delete r;
		
		return status;
	}
private:
	std::shared_ptr<System> pSys;
};

/**
 * Adapter.h header file
 * This file is created by the PIC of LegacyModule
 * to enable the UpgradedModule to access the System
 * without public the source code of the System
 */
class Adapter
{
public:
	Adapter(LegacyModule* lm);
	virtual ~Adapter();
	int GetSystemStatus();

private:
	LegacyModule* module;
};

/**
 * Adapter.cpp source code file 
 * Its implementation is hidden inside the shared object (.so),
 * The PIC of UpgradedModule can only see the interface of Adapter by Adapter.h header file.
 */
Adapter::Adapter(LegacyModule* lm) 
{
	module = lm;
}
Adapter::~Adapter() {}

int Adapter::GetSystemStatus()
{
	printf("%s\n", __func__);
	if (module != nullptr)
	{
		return module->CheckSystemStatus();
	}

	return 0;
}

class UpgradedModule
{
public:
	UpgradedModule(LegacyModule* lm) 
	{
		adap = new Adapter(lm);
	}
	virtual ~UpgradedModule() {}

	void DoRequest()
	{
		printf("%s\n", __func__);
		int status = 0;
		if (adap)
		{
			status = adap->GetSystemStatus();
		}

		if (status == 0)
		{
			return;
		}

		// Do something here
		printf("System is running\n");
	}

private:
	Adapter* adap;
};

int main()
{
	std::shared_ptr<System> sys = std::make_shared<System>();
	UpgradedModule module(new LegacyModule(sys));

	while (true)
	{
		module.DoRequest();
		sleep(1);
	}

	return 0;
}

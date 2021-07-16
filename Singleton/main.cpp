#include <unistd.h>
#include <time.h>
#include <iostream>
#include "singleton.h"

class Database : public Singleton<Database>
{
public:
    void Connect();
    void Disconnect();
};

void Database::Connect()
{
    std::cout << "Connect" << std::endl;
}

void Database::Disconnect()
{
    std::cout << "Disconnect" << std::endl;
}

void * thread_func(void * arg)
{
    Database::GetInstance()->Connect();

    sleep(1);

    Database::GetInstance()->Disconnect();

    pthread_exit((void*)0);
}

int main()
{
    pthread_t t[3];
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&t[i], NULL, thread_func, NULL);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(t[i], NULL);
    }

    return 0;
}
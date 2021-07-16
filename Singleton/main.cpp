#include <iostream>
#include "singleton.h"

class Database : public Singleton<Database>
{
public:
    void Connect();
    void Disconnect();

private:
    friend class Singleton<Database>;
};

void Database::Connect()
{
    std::cout << "Connect" << std::endl;
}

void Database::Disconnect()
{
    std::cout << "Disconnect" << std::endl;
}

int main()
{
    Database::GetInstance()->Connect();
    Database::GetInstance()->Disconnect();

    return 0;
}
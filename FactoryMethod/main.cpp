#include <iostream>
#include <unistd.h>
#include <cstring>
#include <pthread.h>

#include <memory>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iterator>

struct LocationData
{
    double lat;
    double lon;
    double alt;
    int64_t timestamp;
};

class ReceiverInterface;
class ReceiverInterfaceFactory;
class GnssReceiver
{
public:
    GnssReceiver();
    ~GnssReceiver();
    bool initialize(int hardware_version);
    void readLocationData();
    LocationData& getLocationData();
    void DEBUG();

private:
    LocationData m_data;
    ReceiverInterface* m_interface;
    ReceiverInterfaceFactory* m_factory;
};

class ReceiverInterface
{
public:
    virtual bool Open() = 0;
    virtual int32_t Read(void* buffer) = 0;
    virtual int32_t Write(void* buffer) = 0;
protected:
    int m_fd;
};

class UARTInterface : public ReceiverInterface
{
public:
    virtual bool Open() override
    {
        return true;
    }

    virtual int32_t Read(void* buffer) override
    {
        std::string temp = "18 106 0";
        std::memcpy(buffer, temp.c_str(), temp.length());
        return temp.length();
    }

    virtual int32_t Write(void* buffer) override
    {
        return 0;
    }
};

class SOMEIPInterface : public ReceiverInterface
{
public:
    virtual bool Open() override
    {
        return true;
    }

    virtual int32_t Read(void* buffer) override
    {
        std::string temp = "18 106 0";
        std::memcpy(buffer, temp.c_str(), temp.length());
        return temp.length();
    }

    virtual int32_t Write(void* buffer) override
    {
        return 0;
    }
};

class ReceiverInterfaceFactory
{
public:
    ReceiverInterfaceFactory()
    {

    }

    ~ReceiverInterfaceFactory()
    {

    }

    ReceiverInterface* createInterface(int hardware_version)
    {
        ReceiverInterface* interface = nullptr;
        switch (hardware_version)
        {
            case 0:
            {
                interface = new UARTInterface();
                break;
            }
            case 1:
            {
                interface = new SOMEIPInterface();
                break;
            }
            default:
            {
                interface = nullptr;
                break;
            }
        }
        return interface;
    }
};

// Implementation of GnssReceiver class
GnssReceiver::GnssReceiver()
{
    m_data = {};
    m_interface = nullptr;
    m_factory = new ReceiverInterfaceFactory();
}

GnssReceiver::~GnssReceiver()
{
    
}

bool GnssReceiver::initialize(int hardware_version)
{
    m_interface = m_factory->createInterface(hardware_version);
    if (m_interface != nullptr)
    {
        return m_interface->Open();
    }

    return false;
}

void GnssReceiver::readLocationData()
{
    if (m_interface != nullptr)
    {
        char buffer[1024];
        std::memset(buffer, 0, 1024);
        int32_t bytes = m_interface->Read(buffer);
        std::cout << "Read " << bytes << " byte(s): " << buffer << std::endl;
    }
}

LocationData& GnssReceiver::getLocationData()
{
    return m_data;
}

void GnssReceiver::DEBUG()
{
    std::cout << m_data.timestamp << " " << m_data.lat << " " << m_data.lon << " " << m_data.alt << std::endl;
}

int main()
{
    GnssReceiver receiver;
    receiver.initialize(0);
    receiver.readLocationData();
    
    return 0;
}

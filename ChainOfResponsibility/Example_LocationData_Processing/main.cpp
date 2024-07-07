#include <iostream>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <memory>
#include <queue>

struct LocationData
{
    int fixType;
    double lat;
    double lon;
    double alt;
    double speed;
    double accelX;
    double accelY;
    double accelZ;
    double yawRate;
};

class LocationInterface
{
public:
    virtual void getLocationData(std::shared_ptr<LocationData> loc_data) = 0;
};

class LocationManager : public LocationInterface
{
public:
    LocationManager()
    {
        m_data = std::make_shared<LocationData>();
    }

    ~LocationManager()
    {

    }

    virtual void getLocationData(std::shared_ptr<LocationData> loc_data) override
    {
        loc_data->fixType = m_data->fixType;
        loc_data->lat = m_data->lat;
        loc_data->lon = m_data->lon;
        loc_data->alt = m_data->alt;
        loc_data->speed = m_data->speed;
        loc_data->accelX = m_data->accelX;
        loc_data->accelY = m_data->accelY;
        loc_data->accelZ = m_data->accelZ;
        loc_data->yawRate = m_data->yawRate;
    }

    void updateLocationData(std::shared_ptr<LocationData> loc_data)
    {
        m_data->fixType = loc_data->fixType;
        m_data->lat = loc_data->lat;
        m_data->lon = loc_data->lon;
        m_data->alt = loc_data->alt;
        m_data->speed = loc_data->speed;
        m_data->accelX = loc_data->accelX;
        m_data->accelY = loc_data->accelY;
        m_data->accelZ = loc_data->accelZ;
        m_data->yawRate = loc_data->yawRate;

        std::cout << "Updated location data: " << m_data->fixType << " " << m_data->lat << " " << m_data->lon << " " << m_data->alt << std::endl;
    }

private:
    std::shared_ptr<LocationData> m_data;
};

class LocationHandler
{
public:
    LocationHandler()
        : next(nullptr)
    {
    }

    virtual LocationHandler* setNext(LocationHandler* nextHandler)
    {
        next = nextHandler;
        return nextHandler;
    }

    virtual void handle(std::shared_ptr<LocationData> data)
    {
        if (this->next != nullptr)
        {
            this->next->handle(data);   
        }
    }

protected:
    LocationHandler* next;
};

class GnssLocationHandler : public LocationHandler
{
public:
    GnssLocationHandler(std::shared_ptr<LocationManager> service)
    {
        pService = service;
    }

    virtual void handle(std::shared_ptr<LocationData> data) override
    {
        if (data->fixType >= 2)
        {
            pService->updateLocationData(data);
        }

        LocationHandler::handle(data);
    }

private:
    std::shared_ptr<LocationManager> pService;
};

class DeadReckoningHandler : public LocationHandler
{
public:
    DeadReckoningHandler(std::shared_ptr<LocationManager> service)
    {
        pService = service;
        lastKnown = std::make_shared<LocationData>();
    }

    virtual void handle(std::shared_ptr<LocationData> data) override
    {
        if (data->fixType == 1)
        {
            pService->updateLocationData(data);     
        }

        LocationHandler::handle(data);
    }

private:
    std::shared_ptr<LocationManager> pService;
    std::shared_ptr<LocationData> lastKnown;
};

int main()
{
    LocationManager* mainService = new LocationManager();
    LocationHandler* mainHandler = new LocationHandler();
    GnssLocationHandler* gnssHandler = new GnssLocationHandler(std::shared_ptr<LocationManager>(mainService));
    DeadReckoningHandler* drHandler = new DeadReckoningHandler(std::shared_ptr<LocationManager>(mainService));
    mainHandler->setNext(gnssHandler)->setNext(drHandler)->setNext(nullptr);

    std::shared_ptr<LocationData> test_data = std::make_shared<LocationData>();

    test_data->fixType = 3;
    test_data->lat = 18;
    test_data->lon = 106;
    test_data->alt = 0;
    mainHandler->handle(test_data);

    test_data->fixType = 1;
    test_data->lat = 18;
    test_data->lon = 106;
    test_data->alt = 0;
    mainHandler->handle(test_data);

    return 0;
}

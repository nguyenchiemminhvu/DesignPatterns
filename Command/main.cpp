/*
@startuml
class LocationData {
    - lat: double
    - lon: double
    - alt: double
    - timestamp: int64_t
}

class LocationManager {
    - m_data: std::shared_ptr<LocationData>
    + LocationManager()
    + ~LocationManager()
    + updateLocation(data: std::shared_ptr<LocationData>&): void
    + storeLocation(): void
    + reloadLocation(): void
}

abstract class Command {
    - p_locmgr: std::shared_ptr<LocationManager>
    + Command(locmgr: std::shared_ptr<LocationManager>)
    + execute(): void
}

class UpdateLocationCommand {
    - m_data: std::shared_ptr<LocationData>
    + UpdateLocationCommand(locmgr: std::shared_ptr<LocationManager>, loc_data: std::shared_ptr<LocationData>)
    + execute(): void
}

class StoreLocationCommand {
    + StoreLocationCommand(locmgr: std::shared_ptr<LocationManager>)
    + execute(): void
}

class ReloadLocationCommand {
    + ReloadLocationCommand(locmgr: std::shared_ptr<LocationManager>)
    + execute(): void
}

class GnssReceiver {
    - p_locmgr: std::shared_ptr<LocationManager>
    + GnssReceiver()
    + ~GnssReceiver()
    + initialize(locmgr: LocationManager*): void
    + start(): void
    + stop(): void
}

Command <|-- UpdateLocationCommand
Command <|-- StoreLocationCommand
Command <|-- ReloadLocationCommand
LocationData --* LocationManager
GnssReceiver --> Command
LocationManager <-- Command
@enduml
*/

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <unordered_map>
#include <memory>

struct LocationData
{
    double lat;
    double lon;
    double alt;
    int64_t timestamp;
};

class LocationManager
{
public:
    LocationManager()
    {
        m_data = std::make_shared<LocationData>();
    }

    ~LocationManager()
    {

    }

    void updateLocation(std::shared_ptr<LocationData>& data)
    {
        m_data->lat = data->lat;
        m_data->lon = data->lon;
        m_data->alt = data->alt;
        m_data->timestamp = data->timestamp;

        std::cout << "Update location data: " << m_data->timestamp << " " << m_data->lat << " " << m_data->lon << " " << m_data->alt << std::endl;
    }

    void storeLocation()
    {
        std::cout << "Store location data to file" << std::endl;
    }

    void reloadLocation()
    {
        std::cout << "Reload location data from file" << std::endl;
    }
private:
    std::shared_ptr<LocationData> m_data;
};

class Command
{
public:
    Command(std::shared_ptr<LocationManager> locmgr)
    {
        p_locmgr = locmgr;
    }
    virtual void execute() = 0;

protected:
    std::shared_ptr<LocationManager> p_locmgr;
};

class UpdateLocationCommand : public Command
{
public:
    UpdateLocationCommand(std::shared_ptr<LocationManager> locmgr, std::shared_ptr<LocationData> loc_data)
        : Command(locmgr)
    {
        m_data = std::make_shared<LocationData>(*loc_data);
    }

    virtual void execute() override
    {
        if (p_locmgr != nullptr)
        {
            p_locmgr->updateLocation(m_data);
        }
    }
private:
    std::shared_ptr<LocationData> m_data;
};

class StoreLocationCommand : public Command
{
public:
    StoreLocationCommand(std::shared_ptr<LocationManager> locmgr)
        : Command(locmgr)
    {
    }

    virtual void execute() override
    {
        if (p_locmgr != nullptr)
        {
            p_locmgr->storeLocation();
        }
    }
};

class ReloadLocationCommand : public Command
{
public:
    ReloadLocationCommand(std::shared_ptr<LocationManager> locmgr)
        : Command(locmgr)
    {

    }

    virtual void execute() override
    {
        if (p_locmgr != nullptr)
        {
            p_locmgr->reloadLocation();
        }
    }
};

class GnssReceiver
{
public:
    GnssReceiver()
    {
        p_locmgr = nullptr;
    }

    ~GnssReceiver()
    {
    }

    void initialize(LocationManager* locmgr)
    {
        if (locmgr != nullptr)
        {
            p_locmgr = std::shared_ptr<LocationManager>(locmgr);
        }
    }

    void start()
    {
        std::shared_ptr<Command> cmd = std::make_shared<ReloadLocationCommand>(p_locmgr);
        cmd->execute();

        for (int i = 0; i < 10; i++)
        {
            std::shared_ptr<LocationData> data = std::make_shared<LocationData>();
            data->lat = 18;
            data->lon = 106;
            data->alt = 0;
            data->timestamp = i;
            cmd = std::make_shared<UpdateLocationCommand>(p_locmgr, data);
            cmd->execute();
        }
    }

    void stop()
    {
        std::shared_ptr<Command> cmd = std::make_shared<StoreLocationCommand>(p_locmgr);
        cmd->execute();
    }

private:
    std::shared_ptr<LocationManager> p_locmgr;
};

int main()
{
    LocationManager* locmgr = new LocationManager();

    GnssReceiver* receiver = new GnssReceiver();
    receiver->initialize(locmgr);
    
    receiver->start();
    receiver->stop();

    return 0;
}

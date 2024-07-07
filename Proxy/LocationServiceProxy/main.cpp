/*
@startuml
class LocationData {
  - timestamp: int64_t
  - lat: double
  - lon: double
  - alt: double
}

interface LocationInterface {
  + getLocationData(loc_data: std::shared_ptr<LocationData>): void
}

class LocationService {
  - m_data: LocationData
  + LocationService()
  + ~LocationService()
  + getLocationData(loc_data: std::shared_ptr<LocationData>): void
}

class LocationProxy {
  - s_instance: LocationProxy*
  - pService: std::shared_ptr<LocationInterface>
  + getInstance(baseService: LocationInterface* = nullptr): LocationProxy*
  + getLocationData(loc_data: std::shared_ptr<LocationData>): void
}

class Client {
}

LocationData -down-* LocationService
LocationInterface <|.. LocationService
LocationInterface <|.. LocationProxy
LocationProxy -left-> LocationService
Client -up-> LocationProxy
@enduml
*/

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <memory>
#include <queue>

struct LocationData
{
	int64_t timestamp;
    double lat;
    double lon;
    double alt;
};

class LocationInterface
{
public:
	virtual void getLocationData(std::shared_ptr<LocationData> loc_data) = 0;
};

class LocationService;
class LocationProxy : public LocationInterface
{
public:
	static LocationProxy* getInstance(LocationInterface* baseService = nullptr)
	{
		if (s_instance != nullptr)
			return s_instance;
		
		s_instance = new LocationProxy(baseService);
		return s_instance;
	}

	virtual void getLocationData(std::shared_ptr<LocationData> loc_data)
	{
		if (pService != nullptr)
		{
			// Can record access history before handle the request

			pService->getLocationData(loc_data);
		}
	}
private:
	static LocationProxy* s_instance;
	LocationProxy(LocationInterface* baseService = nullptr)
	{
		pService = std::shared_ptr<LocationInterface>(baseService);
	}
	std::shared_ptr<LocationInterface> pService;
};
LocationProxy* LocationProxy::s_instance = nullptr;

class LocationService : public LocationInterface
{
public:
	LocationService()
	{
		m_data = {0, 18, 106, 0};
	}

	~LocationService()
	{

	}

	virtual void getLocationData(std::shared_ptr<LocationData> loc_data) override
	{
		if (loc_data != nullptr)
		{
			loc_data->timestamp = m_data.timestamp;
			loc_data->lat = m_data.lat;
			loc_data->lon = m_data.lon;
			loc_data->alt = m_data.alt;
		}
	}

private:
	LocationData m_data;
};

int main()
{
	LocationService* service = new LocationService();
	LocationProxy::getInstance(service);

	std::shared_ptr<LocationData> data = std::make_shared<LocationData>();
	LocationProxy::getInstance()->getLocationData(data);

	std::cout << data->timestamp << " " << data->lat << " " << data->lon << " " << data->alt << std::endl;

	return 0;
}

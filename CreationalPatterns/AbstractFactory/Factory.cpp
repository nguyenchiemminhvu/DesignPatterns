#include "Factory.h"

namespace AbstractFactory
{
	Product * DellFactory::CreateLaptopProduct(std::string name)
	{
		return new Laptop("DELL", name);
	}

	Product * DellFactory::CreateDesktopProduct(std::string name)
	{
		return new Desktop("DELL", name);
	}

	Product * DellFactory::CreateTabletProduct(std::string name)
	{
		return NULL;
	}

	Product * AsusFactory::CreateLaptopProduct(std::string name)
	{
		return new Laptop("ASUS", name);
	}

	Product * AsusFactory::CreateDesktopProduct(std::string name)
	{
		return new Desktop("ASUS", name);
	}

	Product * AsusFactory::CreateTabletProduct(std::string name)
	{
		return NULL;
	}

	Product * AppleFactory::CreateLaptopProduct(std::string name)
	{
		return new Laptop("APPLE", name);
	}

	Product * AppleFactory::CreateDesktopProduct(std::string name)
	{
		return new Desktop("APPLE", name);
	}

	Product * AppleFactory::CreateTabletProduct(std::string name)
	{
		return new Tablet("APPLE", name);
	}
}
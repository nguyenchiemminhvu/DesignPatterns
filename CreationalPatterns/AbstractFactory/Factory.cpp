#include "Factory.h"

namespace AbstractFactory
{
	ComputerProduct * DellFactory::CreateLaptopProduct(std::string name)
	{
		return new Laptop("DELL", name);
	}

	ComputerProduct * DellFactory::CreateDesktopProduct(std::string name)
	{
		return new Desktop("DELL", name);
	}

	ComputerProduct * DellFactory::CreateTabletProduct(std::string name)
	{
		return NULL;
	}

	ComputerProduct * AsusFactory::CreateLaptopProduct(std::string name)
	{
		return new Laptop("ASUS", name);
	}

	ComputerProduct * AsusFactory::CreateDesktopProduct(std::string name)
	{
		return new Desktop("ASUS", name);
	}

	ComputerProduct * AsusFactory::CreateTabletProduct(std::string name)
	{
		return NULL;
	}

	ComputerProduct * AppleFactory::CreateLaptopProduct(std::string name)
	{
		return new Laptop("APPLE", name);
	}

	ComputerProduct * AppleFactory::CreateDesktopProduct(std::string name)
	{
		return new Desktop("APPLE", name);
	}

	ComputerProduct * AppleFactory::CreateTabletProduct(std::string name)
	{
		return new Tablet("APPLE", name);
	}

	/////////////////////////////////////////////////////////////////

	Chair * ClassicalFurnitureFactory::CreateChair()
	{
		return new ClassicalChair();
	}

	Table * ClassicalFurnitureFactory::CreateTable()
	{
		return new ClassicalTable();
	}

	Chair * ModernFurnitureFactory::CreateChair()
	{
		return new ModernChair();
	}

	Table * ModernFurnitureFactory::CreateTable()
	{
		return new ModernTable();
	}
}
#include "Product.h"

namespace AbstractFactory
{
	int ComputerProduct::__TOTAL = 0;

	ComputerProduct::ComputerProduct(std::string manu, std::string type, std::string name)
		: __pManu(manu)
		, __pType(type)
		, __pName(name)
	{
		__ID = ComputerProduct::__TOTAL++;
	}

	ComputerProduct::~ComputerProduct(void)
	{

	}

	std::string ComputerProduct::GetProductName()
	{
		std::string sID;
		int id = __ID;
		while (id)
		{
			sID.insert(sID.begin(), '0' + (id % 10));
			id /= 10;
		}

		if (sID.empty())
			sID = "0";

		return __pManu + "_" + __pType + "_" + __pName + "_" + sID;
	}

	Laptop::Laptop(std::string manu, std::string name)
		: ComputerProduct(manu, "Laptop", name)
	{

	}

	Laptop::~Laptop()
	{

	}

	Desktop::Desktop(std::string manu, std::string name)
		: ComputerProduct(manu, "Desktop", name)
	{

	}

	Desktop::~Desktop()
	{

	}

	Tablet::Tablet(std::string manu, std::string name)
		: ComputerProduct(manu, "Tablet", name)
	{

	}

	Tablet::~Tablet()
	{

	}

	////////////////////////////////////////////////////////////

	FurnitureProduct::FurnitureProduct()
	{
	}

	FurnitureProduct::~FurnitureProduct()
	{
	}

	Chair::Chair()
		: FurnitureProduct()
	{
	}

	Chair::~Chair()
	{
	}

	ClassicalChair::ClassicalChair()
		: Chair()
	{
	}

	ClassicalChair::~ClassicalChair()
	{
	}

	std::string ClassicalChair::GetType()
	{
		return "ClassicalChair";
	}

	ModernChair::ModernChair()
		: Chair()
	{
	}

	ModernChair::~ModernChair()
	{
	}

	std::string ModernChair::GetType()
	{
		return "ModernChair";
	}

	Table::Table()
		: FurnitureProduct()
	{
	}

	Table::~Table()
	{
	}
	
	ClassicalTable::ClassicalTable()
		: Table()
	{
	}

	ClassicalTable::~ClassicalTable()
	{
	}

	std::string ClassicalTable::GetType()
	{
		return "ClassicalTable";
	}

	ModernTable::ModernTable()
		: Table()
	{
	}

	ModernTable::~ModernTable()
	{
	}

	std::string ModernTable::GetType()
	{
		return "ModernTable";
	}
}
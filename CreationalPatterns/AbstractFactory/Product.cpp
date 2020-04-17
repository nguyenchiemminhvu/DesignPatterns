#include "Product.h"

namespace AbstractFactory
{
	int Product::__TOTAL = 0;

	Product::Product(std::string manu, std::string type, std::string name)
		: __pManu(manu)
		, __pType(type)
		, __pName(name)
	{
		__ID = Product::__TOTAL++;
	}

	Product::~Product(void)
	{

	}

	std::string Product::GetProductName()
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
		: Product(manu, "Laptop", name)
	{

	}

	Laptop::~Laptop()
	{

	}

	Desktop::Desktop(std::string manu, std::string name)
		: Product(manu, "Desktop", name)
	{

	}

	Desktop::~Desktop()
	{

	}

	Tablet::Tablet(std::string manu, std::string name)
		: Product(manu, "Tablet", name)
	{

	}

	Tablet::~Tablet()
	{

	}
}
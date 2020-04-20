#include "Example.h"

#include "Product.h"
#include "Factory.h"

#include <vector>
#include <iostream>

namespace AbstractFactory
{
	void Perform_1()
	{
		ComputerFactory * factory = NULL;
#ifdef __DELL__
		factory = new DellFactory();
#elif __ASUS__
		factory = new AsusFactory();
#else
		factory = new AppleFactory();
#endif

		std::vector<ComputerProduct *> products;

		for (int i = 0; i < 10; i++)
		{
			ComputerProduct * product = factory->CreateLaptopProduct("MACBOOK");
			if (product)
				products.push_back(product);
		}

		for (int i = 0; i < products.size(); i++)
		{
			std::cout << products[i]->GetProductName() << std::endl;
		}

		for (int i = 0; i < products.size(); i++)
		{
			delete products[i];
			products[i] = NULL;
		}
	}

	void Perform_2()
	{
		FurnitureFactory * factory = NULL;
#ifdef __MODERN__
		factory = new ModernFurnitureFactory();
#else
		factory = new ClassicalFurnitureFactory();
#endif

		std::vector<FurnitureProduct *> products;

		for (int i = 0; i < 10; i++)
		{
			FurnitureProduct * product = NULL;
			if (i & 1)
			{
				product = factory->CreateChair();
			}
			else
			{
				product = factory->CreateTable();
			}

			products.push_back(product);
		}

		for (int i = 0; i < 10; i++)
		{
			std::cout << products[i]->GetType() << std::endl;
		}

		for (int i = 0; i < 10; i++)
		{
			delete products[i];
			products[i] = NULL;
		}
	}
}
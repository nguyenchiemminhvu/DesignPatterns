#include "Example.h"

#include "Product.h"
#include "Factory.h"

#include <vector>
#include <iostream>

namespace AbstractFactory
{
	void Perform()
	{
		Factory * factory = NULL;
#ifdef __DELL__
		factory = new DellFactory();
#elif __ASUS__
		factory = new AsusFactory();
#else
		factory = new AppleFactory();
#endif

		std::vector<Product *> products;

		for (int i = 0; i < 10; i++)
		{
			Product * product = factory->CreateLaptopProduct("MACBOOK");
			if (product)
				products.push_back(product);
		}

		for (int i = 0; i < products.size(); i++)
		{
			std::cout << products[i]->GetProductName() << std::endl;
		}
	}
}
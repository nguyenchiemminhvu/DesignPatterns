#include "AbstractFactory/Example.h"
#include "FactoryMethod/Example.h"
#include "Builder/Example.h"
#include "Singleton/Example.h"

int main()
{
	AbstractFactory::Perform_1();
	AbstractFactory::Perform_2();
	FactoryMethod::Perform();
	Builder::Perform();
	Singleton::Perform();

	return 0;
}
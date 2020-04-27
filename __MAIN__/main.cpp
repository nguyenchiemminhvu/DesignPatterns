#include "AbstractFactory/Example.h"
#include "FactoryMethod/Example.h"
#include "Builder/Example.h"
#include "Singleton/Example.h"
#include "Prototype/Example.h"
#include "Adapter/Example.h"

int main()
{
	AbstractFactory::Perform_1();
	AbstractFactory::Perform_2();
	FactoryMethod::Perform();
	Builder::Perform();
	Singleton::Perform();
	Prototype::Perform();
	Adapter::Perform();

	return 0;
}
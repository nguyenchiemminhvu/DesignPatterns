#include "AbstractFactory/Example.h"
#include "FactoryMethod/Example.h"
#include "Builder/Example.h"

int main()
{
	AbstractFactory::Perform_1();
	AbstractFactory::Perform_2();
	FactoryMethod::Perform();
	Builder::Perform();

	return 0;
}
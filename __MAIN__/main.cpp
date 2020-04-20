#include "AbstractFactory/Example.h"
#include "FactoryMethod/Example.h"

int main()
{
	AbstractFactory::Perform_1();
	AbstractFactory::Perform_2();
	FactoryMethod::Perform();

	return 0;
}
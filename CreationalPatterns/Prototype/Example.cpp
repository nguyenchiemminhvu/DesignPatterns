#include "Example.h"

#include "Product.h"
#include "Factory.h"

namespace Prototype
{
	void Perform()
	{
		Factory * factory = new Factory();
		Profile * p = factory->GetProfile(ProfileType::HIGH);
		p->Debug();

		delete factory;
		delete p;
	}
}
#include "Example.h"

#include "Product.h"
#include "Factory.h"

namespace FactoryMethod
{
	void Perform()
	{
		CButtonFactory * factory = new CButtonFactory();
		CButton * button = factory->createButton(ButtonType::C3D_BUTTON);

		if (button)
		{
			button->Render();
		}

		delete button;
		delete factory;
	}
}
#include "Factory.h"

namespace FactoryMethod
{
	CButton * CButtonFactory::createButton(int type)
	{
		CButton * button = NULL;
		switch(type)
		{
		case ButtonType::C2D_BUTTON:
			return new C2DButton();
			break;
		case ButtonType::C3D_BUTTON:
			return new C3DButton();
			break;
		}

		return button;
	}
}
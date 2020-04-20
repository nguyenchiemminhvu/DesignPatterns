#include "Product.h"

#include <iostream>

namespace FactoryMethod
{
	CButton::CButton()
	{
	}

	CButton::~CButton()
	{
	}

	C2DButton::C2DButton()
		: CButton()
	{
	}

	C2DButton::~C2DButton()
	{
	}

	void C2DButton::Render()
	{
		std::cout << "Render 2D Button" << std::endl;
	}

	C3DButton::C3DButton()
		: CButton()
	{
	}

	C3DButton::~C3DButton()
	{
	}

	void C3DButton::Render()
	{
		std::cout << "Render 3D Button" << std::endl;
	}
}
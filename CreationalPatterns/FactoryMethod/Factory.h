#pragma once

#include "Product.h"
#include <queue>
#include <vector>

namespace FactoryMethod
{
	enum ButtonType
	{
		C2D_BUTTON,
		C3D_BUTTON
	};

	class CButtonFactory
	{
	public:
		CButton * createButton(int type);
	};
}
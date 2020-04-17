#pragma once

#include "Product.h"

namespace AbstractFactory
{
	class Factory
	{
	public:
		virtual Product * CreateLaptopProduct(std::string name = "") = 0;
		virtual Product * CreateDesktopProduct(std::string name = "") = 0;
		virtual Product * CreateTabletProduct(std::string name = "") = 0;
	};

	class DellFactory : public Factory
	{
	public:
		virtual Product * CreateLaptopProduct(std::string name = "");
		virtual Product * CreateDesktopProduct(std::string name = "");
		virtual Product * CreateTabletProduct(std::string name = "");
	};

	class AsusFactory : public Factory
	{
	public:
		virtual Product * CreateLaptopProduct(std::string name = "");
		virtual Product * CreateDesktopProduct(std::string name = "");
		virtual Product * CreateTabletProduct(std::string name = "");
	};

	class AppleFactory : public Factory
	{
	public:
		virtual Product * CreateLaptopProduct(std::string name = "");
		virtual Product * CreateDesktopProduct(std::string name = "");
		virtual Product * CreateTabletProduct(std::string name = "");
	};
}

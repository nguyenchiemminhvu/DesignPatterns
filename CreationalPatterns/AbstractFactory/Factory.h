#pragma once

#include "Product.h"

namespace AbstractFactory
{
	class ComputerFactory
	{
	public:
		virtual ComputerProduct * CreateLaptopProduct(std::string name = "") = 0;
		virtual ComputerProduct * CreateDesktopProduct(std::string name = "") = 0;
		virtual ComputerProduct * CreateTabletProduct(std::string name = "") = 0;
	};

	class DellFactory : public ComputerFactory
	{
	public:
		virtual ComputerProduct * CreateLaptopProduct(std::string name = "");
		virtual ComputerProduct * CreateDesktopProduct(std::string name = "");
		virtual ComputerProduct * CreateTabletProduct(std::string name = "");
	};

	class AsusFactory : public ComputerFactory
	{
	public:
		virtual ComputerProduct * CreateLaptopProduct(std::string name = "");
		virtual ComputerProduct * CreateDesktopProduct(std::string name = "");
		virtual ComputerProduct * CreateTabletProduct(std::string name = "");
	};

	class AppleFactory : public ComputerFactory
	{
	public:
		virtual ComputerProduct * CreateLaptopProduct(std::string name = "");
		virtual ComputerProduct * CreateDesktopProduct(std::string name = "");
		virtual ComputerProduct * CreateTabletProduct(std::string name = "");
	};

	///////////////////////////////////////////////////////////////////////

	class FurnitureFactory
	{
	public:
		virtual Chair * CreateChair() = 0;
		virtual Table * CreateTable() = 0;
	};

	class ClassicalFurnitureFactory : public FurnitureFactory
	{
	public:
		virtual Chair * CreateChair();
		virtual Table * CreateTable();
	};

	class ModernFurnitureFactory : public FurnitureFactory
	{
	public:
		virtual Chair * CreateChair();
		virtual Table * CreateTable();
	};
}

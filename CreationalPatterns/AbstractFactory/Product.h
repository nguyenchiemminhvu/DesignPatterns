#pragma once

#include <string>

namespace AbstractFactory
{
	class ComputerProduct
	{
	private:
		static int __TOTAL;

	protected:
		int __ID;
		std::string __pManu;
		std::string __pType;
		std::string __pName;

	public:
		ComputerProduct(std::string manu, std::string pType, std::string name);
		virtual ~ComputerProduct(void);

		virtual std::string GetProductName();
	};

	class Laptop : public ComputerProduct
	{
	public:
		Laptop(std::string manu, std::string name);
		virtual ~Laptop(void);
	};

	class Desktop : public ComputerProduct
	{
	public:
		Desktop(std::string manu, std::string name);
		virtual ~Desktop(void);
	};

	class Tablet : public ComputerProduct
	{
	public:
		Tablet(std::string manu, std::string name);
		virtual ~Tablet(void);
	};

	//////////////////////////////////////////////////////

	class FurnitureProduct
	{
	public:
		FurnitureProduct();
		virtual ~FurnitureProduct();

		virtual std::string GetType() = 0;
	};

	class Chair : public FurnitureProduct
	{
	public:
		Chair();
		virtual ~Chair();
	};

	class ClassicalChair : public Chair
	{
	public:
		ClassicalChair();
		virtual ~ClassicalChair();

		virtual std::string GetType();
	};

	class ModernChair : public Chair
	{
	public:
		ModernChair();
		virtual ~ModernChair();

		virtual std::string GetType();
	};

	class Table : public FurnitureProduct
	{
	public:
		Table();
		virtual ~Table();
	};

	class ClassicalTable : public Table
	{
	public:
		ClassicalTable();
		virtual ~ClassicalTable();

		virtual std::string GetType();
	};

	class ModernTable : public Table
	{
	public:
		ModernTable();
		virtual ~ModernTable();

		virtual std::string GetType();
	};
}

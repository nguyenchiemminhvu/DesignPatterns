#pragma once

#include <string>

namespace AbstractFactory
{
	class Product
	{
	private:
		static int __TOTAL;

	protected:
		int __ID;
		std::string __pManu;
		std::string __pType;
		std::string __pName;

	public:
		Product(std::string manu, std::string pType, std::string name);
		virtual ~Product(void);

		virtual std::string GetProductName();
	};

	class Laptop : public Product
	{
	public:
		Laptop(std::string manu, std::string name);
		virtual ~Laptop(void);
	};

	class Desktop : public Product
	{
	public:
		Desktop(std::string manu, std::string name);
		virtual ~Desktop(void);
	};

	class Tablet : public Product
	{
	public:
		Tablet(std::string manu, std::string name);
		virtual ~Tablet(void);
	};

}

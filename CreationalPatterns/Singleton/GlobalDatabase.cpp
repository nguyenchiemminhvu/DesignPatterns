#include "GlobalDatabase.h"

#include <iostream>

namespace Singleton
{
	GlobalDatabase * GlobalDatabase::instance = 0;

	GlobalDatabase * GlobalDatabase::GetInstance()
	{
		if (!GlobalDatabase::instance)
		{
			GlobalDatabase::instance = new GlobalDatabase();
		}
		return GlobalDatabase::instance;
	}

	GlobalDatabase::GlobalDatabase(void)
	{
	}

	GlobalDatabase::~GlobalDatabase(void)
	{
	}

	void GlobalDatabase::Login(std::string dbname, std::string username, std::string password)
	{
		std::cout << "Login to database: " << dbname << "/" << username << "/" << password << std::endl;
	}
}
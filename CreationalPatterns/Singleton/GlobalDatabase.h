#pragma once

#ifndef __GLOBAL_DATABASE_H__
#define __GLOBAL_DATABASE_H__

#include <string>

namespace Singleton
{
	class GlobalDatabase
	{
	private:
		static GlobalDatabase * instance;

	private:
		GlobalDatabase(void);

	public:
		~GlobalDatabase(void);

		static GlobalDatabase * GetInstance();

		void Login(std::string dbname, std::string username, std::string password);
	};
}
#endif // __GLOBAL_DATABASE_H__
#include "Example.h"

#include "GlobalDatabase.h"

namespace Singleton
{
	void Perform()
	{
		GlobalDatabase::GetInstance()->Login("NONCONDB", "HR", "HR");
	}
}
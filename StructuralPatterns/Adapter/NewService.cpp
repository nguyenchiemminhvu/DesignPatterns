#include "NewService.h"

namespace Adapter
{
	NewService::NewService(void)
	{
		_old_service = new OldService();
	}

	NewService::~NewService(void)
	{
		delete _old_service;
	}

	void NewService::PrintData(std::vector<int> v)
	{
		if (v.empty())
			return;

		_old_service->PrintData((int*)&v[0], v.size());
	}
}
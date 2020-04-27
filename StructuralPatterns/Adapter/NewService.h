#pragma once

#include "OldService.h"

#include <vector>

namespace Adapter
{
	class NewService
	{
	protected:
		OldService *_old_service;

	public:
		NewService(void);
		virtual ~NewService(void);

		void PrintData(std::vector<int> v);
	};
}
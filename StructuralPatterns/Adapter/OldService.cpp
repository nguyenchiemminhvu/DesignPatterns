#include "OldService.h"

#include <iostream>

namespace Adapter
{
	OldService::OldService(void)
	{
	}

	OldService::~OldService(void)
	{
	}

	void OldService::PrintData(int *arr, int n)
	{
		for (int i = 0; i < n; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
}
#pragma once

namespace Adapter
{
	class OldService
	{
	public:
		OldService(void);
		virtual ~OldService(void);

		void PrintData(int *arr, int n);
	};
}
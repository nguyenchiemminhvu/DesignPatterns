#pragma once

#include "NewService.h"

namespace Adapter
{
	class Client
	{
	protected:
		NewService *_service;

	public:
		Client(void);
		virtual ~Client(void);

		void DoLotOfThings();
	};
}
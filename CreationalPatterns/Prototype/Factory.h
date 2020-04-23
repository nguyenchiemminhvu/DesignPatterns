#pragma once

#include "Product.h"

#include <map>

namespace Prototype
{
	class Factory
	{
	private:
		std::map<ProfileType, Profile *> profiles;

	public:
		Factory();
		~Factory();

		Profile * GetProfile(ProfileType type);
	};
}
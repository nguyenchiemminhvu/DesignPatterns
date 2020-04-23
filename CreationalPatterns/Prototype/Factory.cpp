#include "Factory.h"

namespace Prototype
{
	Factory::Factory()
	{
		profiles[ProfileType::LOW] = new ProfileLow();
		profiles[ProfileType::MEDIUM] = new ProfileMedium();
		profiles[ProfileType::HIGH] = new ProfileHigh();
	}

	Factory::~Factory()
	{
		delete profiles[ProfileType::LOW];
		delete profiles[ProfileType::MEDIUM];
		delete profiles[ProfileType::HIGH];
	}

	Profile * Factory::GetProfile(ProfileType type)
	{
		return profiles[type];
	}
}
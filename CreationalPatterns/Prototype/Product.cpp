#include "Product.h"

namespace Prototype
{
	Profile::Profile()
	{
	}

	Profile::~Profile()
	{
	}

	ProfileLow::ProfileLow()
		: Profile()
	{
		profile_name = "Profile Low";
		created_date = "2020/04/23";
		cpu_name = "Intel Core i3";
		gpu_name = "Intel HD Graphics 620";
		ram = "4GB";
	}

	ProfileLow::ProfileLow(const ProfileLow &p)
	{
	}

	ProfileLow::~ProfileLow()
	{
	}

	Profile * ProfileLow::clone()
	{
		return new ProfileLow(*this);
	}

	ProfileMedium::ProfileMedium()
		: Profile()
	{
		profile_name = "Profile Medium";
		created_date = "2020/04/23";
		cpu_name = "Intel Core i5";
		gpu_name = "GeForce 940 MX";
		ram = "8GB";
	}

	ProfileMedium::ProfileMedium(const ProfileMedium &p)
	{
	}

	ProfileMedium::~ProfileMedium()
	{
	}

	Profile * ProfileMedium::clone()
	{
		return new ProfileMedium(*this);
	}

	ProfileHigh::ProfileHigh()
		: Profile()
	{
		profile_name = "Profile HIGH";
		created_date = "2020/04/23";
		cpu_name = "Intel Core i7";
		gpu_name = "GeForce 940 MX";
		ram = "16GB";
	}

	ProfileHigh::ProfileHigh(const ProfileHigh &p)
	{
	}

	ProfileHigh::~ProfileHigh()
	{
	}

	Profile * ProfileHigh::clone()
	{
		return new ProfileHigh(*this);
	}
}
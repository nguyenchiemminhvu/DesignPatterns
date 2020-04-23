#pragma once

#include <string>
#include <iostream>

namespace Prototype
{
	enum ProfileType
	{
		LOW,
		MEDIUM,
		HIGH
	};

	class Profile
	{
	protected:
		std::string profile_name;
		std::string created_date;
		std::string cpu_name;
		std::string gpu_name;
		std::string ram;

	public:
		virtual Profile * clone() = 0;

		virtual void Debug()
		{
			std::cout	<< profile_name << " "
						<< created_date << " "
						<< cpu_name << " "
						<< gpu_name << " " 
						<< ram << std::endl;
		}
	};

	class ProfileLow : public Profile
	{
	public:
		ProfileLow();
		ProfileLow(const ProfileLow &p);
		virtual ~ProfileLow();

		virtual Profile * clone();
	};

	class ProfileMedium : public Profile
	{
	public:
		ProfileMedium();
		ProfileMedium(const ProfileMedium &p);
		virtual ~ProfileMedium();

		virtual Profile * clone();
	};

	class ProfileHigh : public Profile
	{
	public:
		ProfileHigh();
		ProfileHigh(const ProfileHigh &p);
		virtual ~ProfileHigh();

		virtual Profile * clone();
	};
}
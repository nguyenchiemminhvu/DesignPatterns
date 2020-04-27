#include "Client.h"

#include <vector>

namespace Adapter
{
	Client::Client(void)
	{
		_service = new NewService();
	}

	Client::~Client(void)
	{
		delete _service;
	}

	void Client::DoLotOfThings()
	{
		std::string s = "this is a sample string";
		
		std::vector<int> freq(26, 0);
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == ' ')
				continue;

			freq[s[i] - 'a']++;
		}

		_service->PrintData(freq);
	}
}
#include "Example.h"

#include "GameCharacter.h"
#include "Builder.h"

namespace Builder
{
	void Perform()
	{
		MapInfo map;
		map.numNPC = 10;
		map.numPlayer = 3;
		for (int i = 0; i < 10; i++)
		{
			map.playerClass[i] = i % 3;
		}

		GameObjectManager * objectManager = new GameObjectManager();
		objectManager->Load(map);

		// game loop simulator
		{

		}

		delete objectManager;
	}
}
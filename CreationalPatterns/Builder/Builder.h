#pragma once

#include "GameCharacter.h"

#include <vector>

namespace Builder
{
	class GameCharacterBuilder
	{
	public:
		GameCharacterBuilder();
		virtual ~GameCharacterBuilder();

		virtual void SetWeapon(GameCharacter *c, WeaponType type);
		virtual void SetArmor(GameCharacter *c, ArmorType type);
		virtual void SetPotiential(GameCharacter *c, Potiential pot);

		virtual void Make(GameCharacter *c, CharacterClass cc) = 0;
	};

	class PlayerBuilder : public GameCharacterBuilder
	{
	public:
		PlayerBuilder();
		virtual ~PlayerBuilder();

		virtual void Make(GameCharacter *c, CharacterClass cc);
	};

	class NPCBuilder : public GameCharacterBuilder
	{
	public:
		NPCBuilder();
		virtual ~NPCBuilder();

		virtual void Make(GameCharacter *c, CharacterClass cc);
	};
	
	struct MapInfo
	{
		int numNPC;
		int numPlayer;
		int playerClass[255];
	};

	class GameObjectManager
	{
		PlayerBuilder * pBuilder;
		NPCBuilder * nBuilder;

	public:
		std::vector<GameCharacter *> players;
		std::vector<GameCharacter *> NPCs;

		GameObjectManager();
		virtual ~GameObjectManager();

		void Load(MapInfo info);
	};
}
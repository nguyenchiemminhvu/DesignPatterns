#include "Builder.h"

namespace Builder
{
	GameCharacterBuilder::GameCharacterBuilder()
	{
	}

	GameCharacterBuilder::~GameCharacterBuilder()
	{
	}

	void GameCharacterBuilder::SetWeapon(GameCharacter *c, WeaponType type)
	{
		c->weapon = type;
	}

	void GameCharacterBuilder::SetArmor(GameCharacter *c, ArmorType type)
	{
		c->armor = type;
	}

	void GameCharacterBuilder::SetPotiential(GameCharacter *c, Potiential pot)
	{
		c->potiential = pot;
	}

	PlayerBuilder::PlayerBuilder()
		: GameCharacterBuilder()
	{
	}

	PlayerBuilder::~PlayerBuilder()
	{
	}

	void PlayerBuilder::Make(GameCharacter *c, CharacterClass cc)
	{
		if (!c)
			return;

		Potiential pot;
		switch (cc)
		{
		case CharacterClass::ATTACK:
			SetWeapon(c, WeaponType::SWORD);
			SetArmor(c, ArmorType::NONE);

			pot.health = 1000;
			pot.speed = 1.5;
			pot.stamina = 30;
			break;
		case CharacterClass::DEFENSE:
			SetWeapon(c, WeaponType::SHIELD);
			SetArmor(c, ArmorType::IRON);

			pot.health = 1500;
			pot.speed = 1.0;
			pot.stamina = 100;
			break;
		case CharacterClass::SUPPORT:
			SetWeapon(c, WeaponType::RADIO);
			SetArmor(c, ArmorType::FABRIC);

			pot.health = 1000;
			pot.speed = 1.25;
			pot.stamina = 50;
			break;
		}
	}

	NPCBuilder::NPCBuilder()
		: GameCharacterBuilder()
	{
	}

	NPCBuilder::~NPCBuilder()
	{
	}

	void NPCBuilder::Make(GameCharacter *c, CharacterClass cc)
	{
		if (!c)
			return;

		SetWeapon(c, WeaponType::SWORD);
		SetArmor(c, ArmorType::FABRIC);

		Potiential pot;
		pot.health = 100;
		pot.speed = 1.0;
		pot.stamina = 50;
		SetPotiential(c, pot);
	}

	GameObjectManager::GameObjectManager()
	{
		pBuilder = new PlayerBuilder();
		nBuilder = new NPCBuilder();
	}

	GameObjectManager::~GameObjectManager()
	{
		delete pBuilder;
		delete nBuilder;

		for (int i = 0; i < NPCs.size(); i++)
		{
			delete NPCs[i];
		}

		for (int i = 0; i < players.size(); i++)
		{
			delete players[i];
		}
	}

	void GameObjectManager::Load(MapInfo info)
	{
		for (int i = 0; i < info.numNPC; i++)
		{
			GameCharacter * character = new NPCPlayer();
			nBuilder->Make(character, CharacterClass::NPC);
			NPCs.push_back(character);
		}

		for (int i = 0; i < info.numPlayer; i++)
		{
			GameCharacter * character = new Player();
			pBuilder->Make(character, (CharacterClass)info.playerClass[i]);
			players.push_back(character);
		}
	}
}
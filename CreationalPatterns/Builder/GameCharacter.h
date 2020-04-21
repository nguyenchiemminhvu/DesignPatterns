#pragma once

namespace Builder
{
	enum CharacterClass
	{
		ATTACK,
		DEFENSE,
		SUPPORT,
		NPC
	};

	enum WeaponType
	{
		HAND,
		SWORD,
		SHIELD,
		RADIO
	};

	enum ArmorType
	{
		NONE,
		FABRIC,
		IRON
	};

	struct Potiential
	{
		float health;
		float speed;
		float stamina;
	};

	class GameCharacter
	{
	public:
		Potiential potiential;
		ArmorType armor;
		WeaponType weapon;

	public:
		GameCharacter();
		virtual ~GameCharacter();
	};

	class Player : public GameCharacter
	{
	public:
		Player();
		virtual ~Player();
	};

	class NPCPlayer : public GameCharacter
	{
	public:
		NPCPlayer();
		virtual ~NPCPlayer();
	};
}

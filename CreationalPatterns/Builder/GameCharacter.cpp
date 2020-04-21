#include "GameCharacter.h"

namespace Builder
{
	GameCharacter::GameCharacter()
	{
	}

	GameCharacter::~GameCharacter()
	{
	}

	Player::Player()
		: GameCharacter()
	{
	}

	Player::~Player()
	{
	}

	NPCPlayer::NPCPlayer()
		: GameCharacter()
	{
	}

	NPCPlayer::~NPCPlayer()
	{
	}
}
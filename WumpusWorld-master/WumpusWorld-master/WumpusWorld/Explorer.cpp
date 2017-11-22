#include "stdafx.h"
#include "Explorer.h"
#include "NormalLevel.h"

void Explorer::Update()
{
	// anda e toma decisões
	--score;

	auto land = map->GetLand(pos.x, pos.y);
	auto aheadPos = Direction::GetAhead(pos, direction);;
	auto ahead = map->GetLand(pos.x + aheadPos.x, pos.y + aheadPos.y);

	if (!isCarryingChest && land.type == Map::Chest)
	{
		static_cast<NormalLevel*>(GameLevel::activeGameLevel)->PickupChest(pos.x, pos.y);
		isCarryingChest = true;
	}

	if (ahead.type == Map::Wall)
	{
		if (rand() % 2)
		{
			direction = TurnRight(direction);
		}
		else
		{
			direction = TurnLeft(direction);
		}

		return;
	}

	if (land.flags & Land::Stench && arrow > 0)
	{
		//if (rand() % 2)
		{
			isAttacking = true;
			arrow--;
			return;
		}
	}

	if (land.flags & Land::Glow)
	{
		if (ahead.type == Map::Chest)
		{
			MoveForward(aheadPos);
		}
		else
		{
			direction = TurnRight(direction);
		}
		return;
	}

	if (land.flags & Land::Breeze)
	{
		switch (rand() % 7)
		{
		case 0:
		case 1:
			direction = TurnLeft(direction);
			return;
		case 2:
		case 3:
			direction = TurnRight(direction);
			return;

			// case 4 5 6 ele anda para a frente
		}
	}

	MoveForward(aheadPos);
}

void Explorer::Render()
{
	MoveCursor(pos.x, pos.y);
	putchar(direction);
}
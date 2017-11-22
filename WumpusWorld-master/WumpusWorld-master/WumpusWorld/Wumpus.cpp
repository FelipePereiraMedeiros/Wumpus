#include "stdafx.h"
#include "Wumpus.h"
#include "Direction.h"

void Wumpus::Update()
{
	switch (rand() % 5)
	{
	case 0:
		auto ahead = GetAhead(pos, Direction::East);
		
		if (map->GetLand(pos.x + ahead.x, pos.y + ahead.y).type != Map::Wall)
		{
			pos.x += ahead.x;
			pos.y += ahead.y;
		}
		break;
	case 1:
		ahead = GetAhead(pos, Direction::North);

		if (map->GetLand(pos.x + ahead.x, pos.y + ahead.y).type != Map::Wall)
		{
			pos.x += ahead.x;
			pos.y += ahead.y;
		}
		break;
	case 2:
		ahead = GetAhead(pos, Direction::West);

		if (map->GetLand(pos.x + ahead.x, pos.y + ahead.y).type != Map::Wall)
		{
			pos.x += ahead.x;
			pos.y += ahead.y;
		}
		break;
	case 3:
		ahead = GetAhead(pos, Direction::South);

		if (map->GetLand(pos.x + ahead.x, pos.y + ahead.y).type != Map::Wall)
		{
			pos.x += ahead.x;
			pos.y += ahead.y;
		}
		break;
		// case 4 ele fica parado
	}
}

void Wumpus::Render()
{
	// desenha
	MoveCursor(pos.x, pos.y);
	putchar('m');
}
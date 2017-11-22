#pragma once

#include "GameObject.h"
#include "Direction.h"
#include "Map.h"

class Explorer : public GameObject
{
	Map* map;
	struct Position last;
	struct Position pos;
	Direction::Flags direction;
	bool isAttacking;
	bool isCarryingChest;

	void MoveForward(struct Position& ahead)
	{
		last = pos;

		pos.x += ahead.x;
		pos.y += ahead.y;
	}

public:
	int id;
	int score;
	int arrow;
	Explorer() : Explorer(0, 0, Direction::East, nullptr,0) { }
	Explorer(const int x, const int y, const Direction::Flags flags, Map* map,int id)
		: map(map), last({ 0, 0 }), pos({ x, y }), arrow(1), direction(flags), score(0),id(id)
	{
	}

	void Update() override;
	void Render() override;

	int X() const { return pos.x; }
	int Y() const { return pos.y; }

	void ApplyScore(int value) { score += value; }
	bool IsAttacking() { bool aux; aux = isAttacking; isAttacking = false; return aux; }
	bool IsCarryingChest() const { return isCarryingChest; }
	const struct Position& Position() const { return pos; }
	Direction::Flags Direction() const { return direction; }
};


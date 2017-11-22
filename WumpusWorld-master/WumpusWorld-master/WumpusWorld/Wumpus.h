#pragma once

#include "GameObject.h"
#include "Map.h"

class Wumpus : public GameObject
{
	struct Position pos;
	Map* map;

public:
	Wumpus() : Wumpus(0, 0, nullptr) {}

	Wumpus(int x, int y, Map* map)
	{
		pos.x = x;
		pos.y = y;
		this->map = map;
	}

	void Update() override;
	void Render() override;

	int X() const { return pos.x; }
	int Y() const { return pos.y; }
	const struct Position& Position() const { return pos; }
};

#pragma once

#include <string>

using namespace std;

class Land;

class Map
{
	int width;
	int height;

	Land** map;
public:
	Map();
	~Map();

	void Initialize();
	void Generate();

	int& Width() { return width; }
	int& Height() { return height; }

	Land& GetLand(int x, int y) const;
	void PickupChest(int x, int y) const;
	void PlaceChest(int x, int y) const;

	enum Type : unsigned char
	{
		Ground = 176,
		Wall = 219,
		Chest = 157,
		Hole = 233
	};
};

class Land
{
public:
	enum Flags : char
	{
		Breeze = 0x1,
		Glow = 0x2,
		Stench = 0x4
	};

	Map::Type type;
	Flags flags;

	Land(): Land(Map::Ground)
	{
	}

	Land(Map::Type type) : type(type), flags(static_cast<Flags>(0)) {}
};
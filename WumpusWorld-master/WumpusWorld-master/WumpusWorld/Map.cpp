#include "stdafx.h"
#include "Map.h"
enum Map::Type : unsigned char;

Map::Map() : width(0), height(0), map(nullptr)
{
}

Map::~Map()
{
	if (map == nullptr)
		return;

	for (auto i = 0; i < height; i++)
	{
		delete[] map[i];
	}

	delete[] map;
}

void Map::Initialize()
{
	map = new Land*[height];

	for (auto i = 0; i < height; i++)
	{
		map[i] = new Land[width];
	}
}

void Map::Generate()
{

}

Land& Map::GetLand(int x, int y) const
{
	static Land garbage(Wall);

	if (x >= width || x < 0 || y >= height || y < 0)
		return garbage;

	return map[y][x];
}

void Map::PlaceChest(int x, int y) const
{
	map[y][x].type = Chest;
}

void Map::PickupChest(int x, int y) const
{
	map[y][x].type = Ground;
}

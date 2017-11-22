#include "stdafx.h"
#include "NormalLevel.h"
#include <fstream>
#include <algorithm>

NormalLevel::~NormalLevel()
{
	if (map) delete map;

	DeleteWumpuses();

	DeleteExplorers();
}

void NormalLevel::Load()
{
	ifstream stream(filename);
	string buff;

	map = new Map();

	getline(stream, buff);
	map->Width() = stoi(buff.c_str());
	getline(stream, buff);
	map->Height() = stoi(buff);

	map->Initialize();

	DeleteWumpuses();
	DeleteExplorers();
	wumpuses.clear();
	explorers.clear();

	for (auto i = 0; i < map->Height(); i++)
	{
		getline(stream, buff);
		for (auto x = 0; x < map->Width(); x++)
		{
			auto l = &map->GetLand(x, i);

			switch (buff[x])
			{
			case '-':
				break;
			case 'm':
				wumpuses.push_back(new Wumpus(x, i, map));
				ToggleFlag(x, i, Land::Stench);
				break;
			case 'c':
				l->type = Map::Chest;
				ToggleFlag(x, i, Land::Glow);
				break;
			case 'h':
				l->type = Map::Hole;
				ToggleFlag(x, i, Land::Breeze);
				break;
			case 'w':
				l->type = Map::Wall;
				break;
			case '1':
				explorers.push_back(new Explorer(x, i, Direction::North, map,(int) explorers.size()));
				break;
			case '2':
				explorers.push_back(new Explorer(x, i, Direction::South, map, (int) explorers.size()));
				break;
			case '4':
				explorers.push_back(new Explorer(x, i, Direction::West, map, (int)explorers.size()));
				break;
			case '8':
				explorers.push_back(new Explorer(x, i, Direction::East, map, (int) explorers.size()));
				break;
			}
		}
	}
}

bool NormalLevel::ApplyExplorerPosition(Explorer* explorer) const
{
	auto land = map->GetLand(explorer->X(), explorer->Y());

	if (land.type == Map::Hole) // caiu no buraco
	{
		explorer->ApplyScore(Score::Hole);
		return false;
	}

	if (SamePosition(explorer->Position(), { 0, 0 }))
	{
		if (explorer->IsCarryingChest())
		{
			explorer->ApplyScore(Score::Chest);
		}
		return false;
	}

	return true;
}

void NormalLevel::ToggleFlag(int x, int y, Land::Flags flag) const
{
	auto land = &map->GetLand(x - 1, y);	// esquerda
	land->flags = static_cast<Land::Flags>(land->flags ^ flag);

	land = &map->GetLand(x + 1, y);		// direita
	land->flags = static_cast<Land::Flags>(land->flags ^ flag);

	land = &map->GetLand(x, y - 1);		// cima
	land->flags = static_cast<Land::Flags>(land->flags ^ flag);

	land = &map->GetLand(x, y + 1);		// baixo
	land->flags = static_cast<Land::Flags>(land->flags ^ flag);
}

void NormalLevel::Update()
{
	for each (auto wumpus in wumpuses)
	{
		ToggleFlag(wumpus->X(), wumpus->Y(), Land::Stench);
		wumpus->Update();
		ToggleFlag(wumpus->X(), wumpus->Y(), Land::Stench);
	}

	vector<Explorer*> dead;

	for each (auto explorer in explorers)
	{
		
		explorer->Update();

		MoveCursor(0, map->Height() + explorer->id);
		printf("Explorador %d Score: %d Flechas: %d    ", explorer->id, explorer->score,explorer->arrow);

		if (explorer->IsAttacking())
		{
			auto ahead = GetAhead(explorer->Position(), explorer->Direction());

			ahead.x += explorer->Position().x;
			ahead.y += explorer->Position().y;

			wumpuses.erase(remove_if(wumpuses.begin(), wumpuses.end(), [&ahead, &explorer, this](Wumpus* w)
			{
				if (SamePosition(ahead, w->Position()))
				{
					ToggleFlag(w->X(), w->Y(), Land::Stench);
					return true;
				}

				return false;
			}), wumpuses.end());
		}

		for (auto wumpus : wumpuses)
		{
			if (SamePosition(explorer->Position(), wumpus->Position()))
			{
				explorer->ApplyScore(Score::Wumpus);
				MoveCursor(0, map->Height() + 1);
				printf("Explorador %d Score: %d Flechas: %d    ", explorer->id, explorer->score, explorer->arrow);
				ExplorerDied(explorer);
				dead.push_back(explorer);
				break;
			}
		}

		if (!ApplyExplorerPosition(explorer))
		{
			MoveCursor(0, map->Height() + 1);
			printf("Explorador %d Score: %d Flechas: %d    ", explorer->id, explorer->score, explorer->arrow);
			ExplorerDied(explorer);
			dead.push_back(explorer);
			continue;
		}
	}

	explorers.erase(std::remove_if(explorers.begin(), explorers.end(), [&dead](Explorer* e)
	{
		return find(dead.begin(), dead.end(), e) != dead.end();
	}), explorers.end());
}

void NormalLevel::Render()
{
	MoveCursor(0, 0);
	for (auto y = 0; y < map->Height(); y++)
	{
		for (auto x = 0; x < map->Width(); x++)
		{
			putchar(map->GetLand(x, y).type);
		}
		putchar('\n');
	}

	for (auto explorer : explorers) explorer->Render();

	for (auto wumpus : wumpuses) wumpus->Render();
}

bool NormalLevel::Running()
{
	return explorers.size() > 0;
}

void NormalLevel::PickupChest(int x, int y) const
{
	ToggleFlag(x, y, Land::Glow);
	map->PickupChest(x, y);
}

void NormalLevel::ExplorerDied(Explorer* exp) const
{
	if (exp->IsCarryingChest() && map->GetLand(exp->X(), exp->Y()).type != Map::Hole)
	{
		ToggleFlag(exp->X(), exp->Y(), Land::Glow);
		map->PlaceChest(exp->X(), exp->Y());
	}
}

void NormalLevel::PrintEnd() const
{
	MoveCursor(map->Width() + 1, 0);
	puts("O jogo acabou");
}

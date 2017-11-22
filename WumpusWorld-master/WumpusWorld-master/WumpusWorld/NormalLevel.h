#pragma once

#include "GameLevel.h"
#include "Explorer.h"
#include "Map.h"
#include "Wumpus.h"
#include <vector>

class NormalLevel : public GameLevel
{
	vector<Explorer*> explorers;
	vector<Wumpus*> wumpuses;
	Map* map;
	string filename;

	bool ApplyExplorerPosition(Explorer* explorer) const;
	void ToggleFlag(int x, int y, Land::Flags flag) const;

	void DeleteWumpuses() const { if (wumpuses.size()) for each (auto wumpus in wumpuses) delete wumpus; }
	void DeleteExplorers() const { if (explorers.size()) for each (auto explorer in explorers) delete explorer; }

public:
	NormalLevel(string filename) : map(), filename(filename) {}

	virtual ~NormalLevel();

	void PickupChest(int x, int y) const;
	void ExplorerDied(Explorer* exp) const;
	void PrintEnd() const;

	void Load() override;
	void Update() override;
	void Render() override;
	bool Running() override;
};


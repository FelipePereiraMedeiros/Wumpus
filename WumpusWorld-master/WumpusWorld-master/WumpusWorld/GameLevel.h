#pragma once

#include "GameObject.h"

class GameLevel : public GameObject
{
public:
	static GameLevel* activeGameLevel;

	void static LoadGameLevel(GameLevel* gameLevel);

	virtual void Load() = 0;

	virtual bool Running() = 0;
	
};
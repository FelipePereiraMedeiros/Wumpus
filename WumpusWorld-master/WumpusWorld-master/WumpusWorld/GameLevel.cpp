#include "stdafx.h"
#include "GameLevel.h"

GameLevel* GameLevel::activeGameLevel;

void GameLevel::LoadGameLevel(GameLevel* gameLevel)
{
	if (gameLevel == nullptr)
		return;

	gameLevel->Load();
	activeGameLevel = gameLevel;
}
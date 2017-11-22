#include "stdafx.h"
#include "GameLevel.h"

#include <iostream>
#include "NormalLevel.h"
#include <ctime>
using namespace std;
int main()
{
	srand(time(nullptr));

	GameLevel::LoadGameLevel(new NormalLevel("C:\\Users\\Gaspe\\Desktop\\WumpusWorld-master\\WumpusWorld-master\\map.txt"));
	GameLevel::activeGameLevel->Render();

	while (GameLevel::activeGameLevel->Running())
	{
		GameLevel::activeGameLevel->Update();
		GameLevel::activeGameLevel->Render();
		Sleep(1000);
	}

	static_cast<NormalLevel*>(GameLevel::activeGameLevel)->PrintEnd();

	_gettch();
    return 0;
}


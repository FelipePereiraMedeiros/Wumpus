// stdafx.h : arquivo de inclusão para inclusões do sistema padrões,
// ou inclusões específicas de projeto que são utilizadas frequentemente, mas
// são modificadas raramente
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <Windows.h>

extern HANDLE console;
extern COORD cursorPosition;

struct Position
{
	int x;
	int y;
};

extern bool SamePosition(const struct Position& p1, const struct Position& p2);

inline void MoveCursor(const int& x, const int& y)
{
	cursorPosition.X = x;
	cursorPosition.Y = y;
	SetConsoleCursorPosition(console, cursorPosition);
}

namespace Score
{
	const int Hole = -500;
	const int Wumpus = -1000;
	const int Chest = 1000;
	const int Kill = 500;
}
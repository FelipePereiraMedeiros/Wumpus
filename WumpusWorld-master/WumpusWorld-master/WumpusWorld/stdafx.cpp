// stdafx.cpp : arquivo de origem que inclui apenas as inclusões padrões
// $safeprojectname$.pch será o cabeçalho pré-compilado
// stdafx.obj conterá as informações de tipo pré-compiladas

#include "stdafx.h"

// TODO: referencie qualquer cabeçalho adicional necessário em STDAFX.H
// e não neste arquivo
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorPosition;

bool SamePosition(const struct Position& p1, const struct Position& p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}
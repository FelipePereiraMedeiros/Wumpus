#pragma once

namespace Direction
{
	enum Flags : unsigned char
	{
		North = 193,
		South = 194,
		West = 180,
		East = 195
	};

	extern struct Position GetAhead(struct Position pos, Flags f);
	extern Flags TurnRight(Flags f);
	extern Flags TurnLeft(Flags f);
}
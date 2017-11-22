#include "stdafx.h"
#include "Direction.h"

Position Direction::GetAhead(Position pos, Flags f)
{
	switch (f)
	{
	case Direction::North:
		return { 0, -1 };
	case Direction::South:
		return { 0, 1 };
	case Direction::West:
		return { -1, 0 };
	case Direction::East:
		return { 1, 0 };
	default:
		return { 0, 0 };
	}
}

Direction::Flags Direction::TurnRight(Flags f)
{
	switch (f)
	{
	case Direction::North:
		return Direction::East;
	case Direction::South:
		return Direction::West;
	case Direction::West:
		return Direction::North;
	case Direction::East:
		return Direction::South;
	default: return static_cast<Direction::Flags>(0);
	}
}

Direction::Flags Direction::TurnLeft(Flags f)
{
	switch (f)
	{
	case Direction::North:
		return Direction::West;
	case Direction::South:
		return Direction::East;
	case Direction::West:
		return Direction::South;
	case Direction::East:
		return Direction::North;
	default: return static_cast<Direction::Flags>(0);
	}
}

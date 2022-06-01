#include "Player.h"
//#include <cstdlib>
//#include "Board.h"

bool Player::move(char command, int size_x, int size_y)
{
	switch (command)
	{
	case 'w':
		if (coordinate_y != 0)
			coordinate_y--;
		else
			return 0;
		break;

	case 'a':
		if (coordinate_x != 0)
			coordinate_x--;
		else
			return 0;
		break;

	case 's':
		if (coordinate_y < size_y - 1)
			coordinate_y++;
		else
			return 0;
		break;

	case 'd':
		if (coordinate_x < size_x - 1)
			coordinate_x++;
		else
			return 0;
		break;

	default:
		return 0;
	}

	return 1;
}

bool Player::move(int direction, int size_x, int size_y, Player objective)
{
	switch (direction)
	{
	case 0:
		if (coordinate_y != 0 &&coordinate_y-1!=objective.coordinate_y)
			coordinate_y--;
		else
			return 0;
		break;

	case 1:
		if (coordinate_x != 0 && coordinate_x - 1 != objective.coordinate_x)
			coordinate_x--;
		else
			return 0;
		break;

	case 2:
		if (coordinate_y < size_y - 1 && coordinate_y + 1 != objective.coordinate_y)
			coordinate_y++;
		else
			return 0;
		break;

	case 3:
		if (coordinate_x < size_x - 1 && coordinate_x + 1 != objective.coordinate_x)
			coordinate_x++;
		else
			return 0;
		break;

	default:
		return 0;
	}

	return 1;
}
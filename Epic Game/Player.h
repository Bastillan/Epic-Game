#pragma once

class Player
{
private:
	
public:
	int coordinate_x;
	int coordinate_y;
	char marker;
	int localization;
	int possible_movement;

	bool move(char command, int size_x, int size_y);
	bool move(int direction, int size_x, int size_y, Player objective);
};


#pragma once

class Player
{
private:
	
public:
	int coordinate_x;
	int coordinate_y;
	char marker;
	int localization;

	bool move(char command, int size_x, int size_y); // main_player movement
	bool move(int direction, int size_x, int size_y); // objective movement
	bool move(int direction); //enemies movement
};


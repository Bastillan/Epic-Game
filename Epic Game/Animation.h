#pragma once

#include <string>

class Animation
{
public:
	bool end_game_animation(std::string map_output, int coordinate_x, int coordinate_y, int size_x, int size_y, bool has_won, int width);
};


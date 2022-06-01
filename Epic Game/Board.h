#pragma once

#include <string>
#include "Player.h"

class Board
{
private:
	int size_x;
	int size_y;
	int number_of_enemies;
	std::string map_clear;
	std::string map_output;
	int width;
	int level_of_difficulty;

public:
	Board(int size_x, int size_y, int level); //konstruktor
	Player main_player;
	Player* enemy; // pointer
	Player objective;

	int result;
	bool result_checking();
	bool checking_for_standing_on_enemy();

	bool set_up_game();
	bool display_board();
	bool spawn_objective();
	bool spawn_main_player();
	bool spawn_enemies();
	bool update_map();
	int calculation_of_localization(Player player);
	bool gameplay();

	int calculation_of_possible_movement(Player player);
	bool enemy_movement();

};


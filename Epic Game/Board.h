#pragma once

#include <string>
#include "Player.h"
#include "Animation.h"

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
	bool objective_movement;
	int counter; // licznik dla poruszania objective (jesli counter jest podzielny przez 3 to wykonuje ruch)

public:
	Board(int size_x, int size_y, int level, bool objective_movement); //konstruktor
	Player main_player;
	Player* enemy; // pointer
	Player objective;
	Animation animation_handling;

	bool set_up_game();
	bool spawn_main_player();
	bool spawn_objective();
	bool spawn_enemies();

	bool display_board();
	bool update_map();
	int calculation_of_localization(Player player);

	bool gameplay();
	bool objective_movement_function();

	bool enemy_movement();
	std::string which_directions_possible(int i, bool layout[], bool enemies_left[]);
	bool will_cover_sb(int coordinates, bool layout[], bool enemies_left[]);
	bool can_move(int coordinates, bool layout[]);

	int result;
	bool result_checking();
	bool checking_for_standing_on_enemy();

	bool end_game();
};


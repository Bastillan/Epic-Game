#include "Board.h"
#include <iostream>
#include <windows.h> // COORD, SetConsuleCursorPosition(), Beep()
#include <conio.h> // getch()
#include <set>
#include <cstdlib> // exit()

Board::Board(int size_x, int size_y, int level)
{
	this->size_x = size_x;
	this->size_y = size_y;

	if(level==1)
		number_of_enemies = (size_x * size_y) / 5;
	else
		number_of_enemies = (size_x * size_y) / 3;
	
	map_clear = "";

	for (int i = 0; i <= size_y; ++i)
	{
		for (int j = 0; j <= size_x; ++j)
		{
			if (j == size_x)
			{
				if (i == 0)
					map_clear += " ";
				else
					map_clear += "|";
			}
			else
			{
				if (i == 0)
					map_clear += " _";
				else
					map_clear += "|_";
			}
		}

		map_clear += "\n";
	}

	map_output = map_clear;
	width = (size_x + 1) * 2; // pola+|+\n
	result = 0;
}

bool Board::set_up_game()
{
	spawn_main_player();
	spawn_objective();

	enemy = new Player[number_of_enemies];

	spawn_enemies();
	
	system("CLS");
	display_board();

	return 1;
}

bool Board::spawn_main_player()
{
	main_player.marker = 'X';
	main_player.coordinate_x = rand() % size_x;
	main_player.coordinate_y = size_y-1;

	return 1;
}

bool Board::spawn_objective()
{
	objective.marker = char(219);
	objective.coordinate_x = rand() % size_x;
	objective.coordinate_y = rand() % (size_y - 5);

	return 1;
}

bool Board::spawn_enemies()
{
	std::set<std::pair<int, int>> positions;

	positions.insert(std::make_pair(objective.coordinate_x, objective.coordinate_y));

	for (int i = 0; i < number_of_enemies; ++i)
	{
		int c_x= rand() % size_x;
		int c_y= rand() % (size_y - 2);

		while (positions.count(std::make_pair(c_x, c_y))!=0)
		{
			c_x = rand() % size_x;
			c_y = rand() % (size_y - 2);
		}

		positions.insert(std::make_pair(c_x, c_y));

		enemy[i].marker = 'O';
		enemy[i].coordinate_x = c_x;
		enemy[i].coordinate_y = c_y;
	}

	return 1;
}

bool Board::display_board()
{
	COORD coordinate;
	coordinate.X = 0;
	coordinate.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);

	update_map();

	std::cout << "Type direction [WSAD] or x to exit" << std::endl;
	std::cout << map_output << std::endl;

	return 1;
}

bool Board::update_map()
{
	map_output = map_clear;

	objective.localization = calculation_of_localization(objective);
	map_output[objective.localization] = objective.marker;

	for (int i = 0; i < number_of_enemies; ++i)
	{
		enemy[i].localization = calculation_of_localization(enemy[i]);
		map_output[enemy[i].localization] = enemy[i].marker;
	}

	main_player.localization = calculation_of_localization(main_player);
	map_output[main_player.localization] = main_player.marker;

	return 1;
}

int Board::calculation_of_localization(Player player)
{
	int output_localization = (player.coordinate_y + 1) * width + (player.coordinate_x + 1) * 2 - 1;

	return output_localization;
}

bool Board::checking_for_standing_on_enemy()
{
	for (int i = 0; i < number_of_enemies; ++i)
	{
		if (enemy[i].localization == main_player.localization)
			return 1;
	}

	return 0;
}

bool Board::result_checking()
{
	if (main_player.localization == objective.localization)
		result = 1;
	else if (checking_for_standing_on_enemy())
		result = -1;

	return 1;
}

int Board::calculation_of_possible_movement(Player player)
{
	int options = 4;

	if (player.coordinate_x == 0 || objective.coordinate_x == player.coordinate_x - 1)
		options--;
	if (player.coordinate_x == size_x - 1 || objective.coordinate_x == player.coordinate_x + 1)
		options--;
	if (player.coordinate_y == 0 || objective.coordinate_y == player.coordinate_y - 1)
		options--;
	if (player.coordinate_y == size_y - 1 || objective.coordinate_y == player.coordinate_y + 1)
		options--;

	return options;
}

bool Board::enemy_movement()
{
	int direction = 0;

	for (int i = 0; i < number_of_enemies; ++i)
	{
		direction = rand() % 4;

		while(!enemy[i].move(direction, size_x, size_y, objective))
			direction = rand() % 4;
	}

	return 1;
}



bool Board::gameplay()
{
	char command;
	
	while (true)
	{
		command = _getch();

		if (command == 'x') // wyjscie z gry
			exit(0);

		while (!main_player.move(command, size_x, size_y))
		{
			Beep(220, 75); // wydanie dzwieku

			command = _getch();

			if (command == 'x') // wyjscie z gry
				exit(0);
		}

		enemy_movement();

		display_board();
		result_checking();

		if (result!=0) // jesli gra sie skonczy
			break;
	}

	return 1;
}

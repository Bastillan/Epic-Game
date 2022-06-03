#include "Animation.h"
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <wincon.h>

bool Animation::end_game_animation(std::string map_output, int coordinate_x, int coordinate_y, int size_x, int size_y, bool has_won, int width)
{
	HANDLE output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordinates;
	coordinates.X = 0;
	coordinates.Y = 0;

	int char_to_player_distance, char_coordinates, starting_position, number_of_frames;
	unsigned int sleep_time = (unsigned int)(210 / sqrt(sqrt(size_x * size_y)));

	if (has_won)
		number_of_frames = (int)(sqrt(fmax(size_x-coordinate_x-1, coordinate_x)*fmax(size_y-coordinate_y-1, coordinate_y)) + 5);
	else
		number_of_frames = (int)(sqrt(pow(fmax(size_x - coordinate_x - 1, coordinate_x) + 1, 2) + pow(fmax(size_y - coordinate_y - 1, coordinate_y) + 1, 2)) + 4);

	for (int i = 0; i < number_of_frames; ++i)
	{
		if (has_won)
			starting_position = 0; // problem z wyliczaniem nuber_of_frames w przypadku zwyciestwa na bardzo szerokiej mapie
			//starting_position = (int)fmax(coordinate_x - i, 0);
		else
			starting_position = (int)(size_x * fmax(coordinate_y - i, 0) + fmax(coordinate_x - i, 0));

		for (int a = starting_position; a <= (size_x * size_y)-1; ++a)
		{
			if (has_won)
				char_to_player_distance = abs(a % size_x - coordinate_x) * abs(a / (size_x)-coordinate_y);
			else
				char_to_player_distance = (int)(pow(abs(a % size_x - coordinate_x), 2) + pow(abs(a / (size_x)-coordinate_y), 2));

			char_coordinates = (a / size_x) * (width)+width + a % size_x * 2 + 1;

			if (char_to_player_distance <= abs(i - 3) * (i - 3))
				map_output[char_coordinates] = '_';
			else if (char_to_player_distance <= abs(i - 2) * (i - 2))
				map_output[char_coordinates] = char(176);
			else if (char_to_player_distance <= abs(i - 1) * (i - 1))
				map_output[char_coordinates] = char(178);
			else if (char_to_player_distance <= i * i)
				map_output[char_coordinates] = char(219);
		}

		Sleep(sleep_time);
		SetConsoleCursorPosition(output_handle, coordinates);

		std::cout << "Type direction [WSAD] or x to exit" << std::endl;
		std::cout << map_output << std::endl;
	}

	std::string end_game_message;

	if (has_won)
	{
		SetConsoleTextAttribute(output_handle, BACKGROUND_GREEN);
		end_game_message = "\nCONGRATULATIONS, YOU HAVE WON!!!\n";
	}
	else
	{
		SetConsoleTextAttribute(output_handle, BACKGROUND_RED);
		end_game_message = "\nGAME OVER, YOU HAVE LOST!!!\n";
	}
	
	for (int i = 0; i < end_game_message.length(); ++i)
	{
		std::cout << end_game_message[i];
		Sleep(59);
	}

	SetConsoleTextAttribute(output_handle, FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);

	Sleep(3000); // Oczekiwanie po zakonczeniu rozgrywki

	return 1;
}

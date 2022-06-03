// Epic Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib> // srand, rand
#include <cstdio> // NULL
#include <ctime> // time
#include <Windows.h>// Beep()
#include "Board.h"

std::pair <int, int> map_size_function()
{
	COORD c2 = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));

	int supplementary = c2.X;
	int max_x;

	if (supplementary % 2 == 1)
		max_x = supplementary / 2;
	else
		max_x = supplementary / 2 - 1;

	int max_y = c2.Y - 8;

	int x, y;

	std::cout << "Enter width of the map (integer number greater than 5 but maximum - "<<max_x<<"): ";
	std::cin >> x;

	bool control = std::cin.fail();

	while (control || x<6 || x>max_x)
	{
		Beep(1220, 75);

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "You have entered invalid number\nTry again." << std::endl;
		std::cin >> x;

		control = std::cin.fail();
	}

	std::cout << "Enter length of the map (integer number greater than 5 but maximum - "<<max_y<<"): ";
	std::cin >> y;

	control = std::cin.fail();

	while (control || y<6 || y>max_y)
	{
		Beep(1220, 75);

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "You have entered invalid number\nTry again." << std::endl;
		std::cin >> y;

		control = std::cin.fail();
	}

	std::pair <int, int> map_size = std::make_pair(x, y);

	return map_size;
}

int main_interface()
{
	std::cout << "Epic Game\nWhat game mode would you like to play?\nTo play Standard Mode enter 1.\nTo play Pursuit Mode enter 2.\nTo exit enter 3.\n";
	int command;
	std::cin >> command;

	bool control = std::cin.fail();
	
	while (control)
	{
		Beep(520, 75);

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "You have entered invalid number\nTry again." << std::endl;
		std::cin >> command;

		control = std::cin.fail();
	}

	return command;
}

int choosing_level_of_difficulty()
{
	int level = 0;

	std::cout << "Choose level of difficulty\n1. Easy\n2. Normal\n3. Difficult\n";
	std::cin >> level;

	bool control = std::cin.fail();

	while (control||level<1||level>3)
	{
		Beep(520, 75);

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "You have entered invalid number\nTry again." << std::endl;
		std::cin >> level;

		control = std::cin.fail();
	}

	return level;
}

bool game_mode(bool objective_movement)
{
	//srand(time(NULL));
	srand((unsigned int)time(NULL));

	int level = choosing_level_of_difficulty();

	std::pair <int, int> map_size = map_size_function();

	Board main_board(map_size.first, map_size.second, level, objective_movement);

	std::cout << "Everything is ready. Press ENTER\n";
	std::cin.ignore(INT_MAX, '\n');
	std::cin.get();

	main_board.set_up_game();
	main_board.gameplay();
	main_board.end_game();

	delete[] main_board.enemy;

	return 1;
}

bool console_options()
{
	SetConsoleTitleA("Epic Game");
	
	HWND hwnd = GetConsoleWindow(); // pobieranie uchwytu okna konsoli
	ShowWindow(hwnd, SW_SHOWMAXIMIZED); // maksymalizacja okna konsoli

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c2 = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE)); // zwracanie maksymalnych rozmiarów
	SetConsoleScreenBufferSize(handle, c2); // ustawiasz rozmiar bufora 
	SMALL_RECT sr;
	sr.Left = 0;
	sr.Top = 0;
	sr.Right = c2.X - 1;
	sr.Bottom = c2.Y - 1;
	SetConsoleWindowInfo(handle, true, &sr); // ustawiasz rozmiar okna (jednostka to szerokoœæ i wysokoœæ pojedynczego znaku)
	
	//std::cout << c2.X/2 << " " << c2.Y-8 << std::endl; // potencjalne obliczanie maksymalnej mapy

	return 1;
}

bool game_handling()
{
	int interface_command = main_interface();

	switch (interface_command)
	{
	case 1:
		game_mode(0); // without objective_movement
		break;
	case 2:
		game_mode(1); // with objective_movement (it moves once three turns)
		break;
	case 3:
	default:
		exit(0);
	}

	return 1;
}

bool next_game()
{
	std::cout << "Would you like to play again?\n(Enter 1 if yes, or 2 if no)\n";
	int command;
	std::cin >> command;

	bool control = std::cin.fail();

	while (control)
	{
		Beep(520, 75);

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "You have entered invalid number\nTry again." << std::endl;
		std::cin >> command;

		control = std::cin.fail();
	}

	system("CLS");

	if (command == 1)
		return 1;
	else
		return 0;
}

int main()
{
	console_options();

	game_handling();

	bool another_game = next_game();

	while (another_game)
	{
		game_handling();
		another_game = next_game();
	}

	//std::cin.get();

	return 0;
}

//Game mode
//Standard mode: Objective is not moving, Enemies are
//Pursuit mode: Objectice is moving, Enemies as well

//Difficulty level
//Normal: number_of_enemies=size_x*size_y/3
//Easy: number_of_enemies=size_x*size_y/6


//Opcja kustomizacji markerow?
//Dostosowywanie rozmiaru do poszczegolnych monitorow



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

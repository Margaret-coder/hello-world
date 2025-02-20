#include <Windows.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <map>
#include <iterator> 
#include "Types.h"
#include "Field.h"

#pragma once
using namespace std;

// View.h

class View
{
	HANDLE hOut_ = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	COORD offset;
	char const * str;
	int keyboard_key;
	//Coord falling_figure_previous_left_top_point; not needed
	array<COORD, 4> next_figure_previous_state; // for next figure previous display deleting
public:
	View();
	View(Field game_field);
	View::~View();
//	void DrawField(Field const &game_field); ����� �� ������
//	const char* ViewAction(Field const &game_field);
	void DrawField(Field const game_field);
	const char* ViewAction(Field const game_field);
};


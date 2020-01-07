#include "View.h"
#include <iostream>
using namespace std;

// View.cpp

View::View()
{
}

View::View(Field _game_field)
{
	next_figure_previous_state = _game_field.get_next_figure().get_figure_coord();
	offset.x = 10;
	offset.y = 1;
	keyboard_key = 0;
	system("color 3e");
	CONSOLE_CURSOR_INFO cInfo = { 100, false };
	SetConsoleCursorInfo(hOut_, &cInfo);
}

View::~View()
{
}

void View::DrawField(Field game_field) {

	COORD c;
	c.X = offset.x;
	c.Y = offset.y;
	int width = game_field.get_width();
	int height = game_field.get_height();
	int num = 0;
	for (int i = 0; i <= width; i++)
	{
		c.Y = i + offset.y;
		SetConsoleTextAttribute(hOut_, BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		SetConsoleCursorPosition(hOut_, c);
		for (int j = 0; j <= height; j++)
		{
			if (i == 0 && j == 0)cout << char(0xDA);	
			else if (i == 0 && j == height) cout << char(0xBF);
			else if (i == width && j == 0) cout << char(0xC0);
			else if (i == width && j == height) cout << char(0xD9);
			else if (j == 0 || j == height)cout << char(0xB3); 
			else if (i == 0 || i == width)cout << char(0xC4); 
			else if (game_field.get_cell_value_by_indexes(j, i) != 0) // i, j! странная вьюха
				cout << "*";
				//cout << char(0xDB) << char(0xDB);
			else cout << " ";
		}
		SetConsoleTextAttribute(hOut_, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
		if (i > 0) cout << ' '; // shadow
		SetConsoleTextAttribute(hOut_, BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		if (i < height && i > 0) cout << num++; // vertical numbers
		cout << '\n';
	}
	num = 0;
	c.X++;
	c.Y++;
	SetConsoleTextAttribute(hOut_, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
	SetConsoleCursorPosition(hOut_, c);
	for (int j = 0; j < width; ++j) // horizontal shadow
		cout << " ";
	cout << " ";
	c.Y++;
	SetConsoleTextAttribute(hOut_, BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	SetConsoleCursorPosition(hOut_, c);
	for (int j = 0; j < width/2; ++j)
		cout << num++ << "  ";

	// предпоказ следующей фигуры
	SetConsoleTextAttribute(hOut_, BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	for (int i = 0; i < game_field.get_next_figure().get_figure_coord().size(); i++) {
		c.X = offset.x * 2 + game_field.get_width() + next_figure_previous_state[i].x;
		c.Y = offset.y + next_figure_previous_state[i].y + 1;
		SetConsoleCursorPosition(hOut_, c);
		cout << " ";
	}
	next_figure_previous_state = game_field.get_next_figure().get_figure_coord();
	for (int i = 0; i < game_field.get_next_figure().get_figure_coord().size(); i++) {
		c.X = offset.x * 2 + game_field.get_width() + game_field.get_next_figure().get_figure_coord()[i].x;
		c.Y = offset.y + game_field.get_next_figure().get_figure_coord()[i].y + 1;
		SetConsoleCursorPosition(hOut_, c);
		cout << "*";
		cout << endl;
		cout << game_field.get_next_figure().get_figure_coord()[i].x << " ";
		cout << game_field.get_next_figure().get_figure_coord()[i].y;
	}
}

const char* View::ViewAction(Field game_field) { // работает конструктор копирования
	//for (int j = 0; j < game_field.get_width(); j++)
	//{
	//	cout << endl;
	//		for (int i = 0; i < game_field.get_height(); i++) // почему фигура падает вправо, а не вниз?
	//		{
	//		cout << game_field.get_cell_value_by_indexes(i, j);
	//		cout << " ";
	//	}
	//}
	//cout << endl;
	//cout << "x = " << game_field.get_figure_left_top_point().x;
	//cout << " ";
	//cout << "y = " << game_field.get_figure_left_top_point().y;
	char const *  str = "";
	if (_kbhit()) {
		keyboard_key = _getch();
		FlushConsoleInputBuffer(hIn);
		if (keyboard_key == static_cast<int>(actions::MIN) || keyboard_key == static_cast<int>(actions::MAX)) {
			keyboard_key = _getch();
			switch (keyboard_key) {
			case static_cast<int>(actions::UP) : return "UP";
			case static_cast<int>(actions::LEFT) : return  "LEFT";
			case static_cast<int>(actions::RIGHT) : return  "RIGHT";
			case static_cast<int>(actions::DOWN) : return "DOWN";
			}
		}
		else { 
			FlushConsoleInputBuffer(hIn); 
			keyboard_key = static_cast<int>(actions::MIN);
		}
	return str;
	}
}
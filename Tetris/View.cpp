#include "View.h"
#include <iostream>
using namespace std;

// View.cpp

View::View()
{
}

View::View(Field _game_field)
{
	falling_figure_previous_state = _game_field.get_figure().get_figure_coord();
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
	int** game_field_cells;// = game_field.get_field_cells();
	game_field_cells = new int*[game_field.get_width()];
	for (int i = 0; i < game_field.get_width(); i++)
	{
		game_field_cells[i] = new int[game_field.get_height()];
		for (int j = 0; j < game_field.get_height(); j++) {
			game_field_cells[i][j] = game_field.get_field_cells()[i][j];
		}
	}
	for (int i = 0; i < game_field.get_width(); i++)
	{
		
		for (int j = 0; j < game_field.get_height(); j++) {
			cout << game_field_cells[j][i] << ' ';
		}
		cout << endl;
	}
 
	array<Coord, 4> temp_figure_coord = game_field.get_figure().get_figure_coord();
	COORD c;
	c.X = offset.x;
	c.Y = offset.y;
	int width = game_field.get_width();
	int height = game_field.get_height();
	int i = 0, j = 0, num = 0;
	SetConsoleCursorPosition(hOut_, c);
	SetConsoleTextAttribute(hOut_, BACKGROUND_BLUE | BACKGROUND_GREEN);
	while (i <= height)
	{
		c.Y = i + offset.y;
		SetConsoleTextAttribute(hOut_, BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		SetConsoleCursorPosition(hOut_, c);
		j = 0;
		while (j <= width)
		{
			if (i == 0 && j == 0)cout << char(0xDA);	
			else if (i == 0 && j == width) cout << char(0xBF);
			else if (i == height && j == 0) cout << char(0xC0);
			else if (i == height && j == width) cout << char(0xD9);
			else if (j == 0 || j == width)cout << char(0xB3); 
			else if (i == 0 || i == height)cout << char(0xC4); 
			else if (game_field_cells[j][i]) 
				cout << "*";
				//cout << char(0xDB) << char(0xDB);
			else cout << " ";
			++j;
		}
		SetConsoleTextAttribute(hOut_, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
		if (i > 0) cout << ' '; // shadow
		SetConsoleTextAttribute(hOut_, BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		if (i < width && i > 0) cout << num++; // vertical numbers
		cout << '\n';
		++i;
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
}

const char* View::ViewAction(Field game_field) {
	int** game_field_cells = game_field.get_field_cells();
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
#include "Field.h"
#include <iostream>
#include <conio.h>
using namespace std;

using namespace std;

// Field.cpp

// Model

Field::Field()
{
//	width = 20;
//	height = 20;
	width = 8;
	height = 8;
	field_cells = new int*[width];
	for (int i = 0; i < width; i++)
	{
		field_cells[i] = new int[height];
		for (int j = 0; j < height; j++) {
			field_cells[i][j] = 0; 
		}
	}
	falling_figure_left_top_point.x = width / 2 - 1;
	falling_figure_left_top_point.y = 1;
}

Field::Field(int _width, int _height)
{
	width = _width;
	height = _height;
	falling_figure_left_top_point.x = width / 2 - 1;
}

// Copy constructor - не работает. У меня тут пробел в знаниях
Field::Field(const Field& f)
{
	width = f.width;
	height = f.height;

	field_cells = new int*[width];

	for (int i = 0; i < f.width; i++)
	{
		field_cells[i] = new int[height];
		for (int j = 0; j < f.height; j++)
		{
			field_cells[i][j] = f.field_cells[i][j];
		}
	}
}

Field& Field:: operator=(Field const& f) { // тоже какая-то фигня
	width = f.width;
	height = f.height;

	field_cells = new int*[width];

	for (int i = 0; i < width; i++)
	{
		field_cells[i] = new int[height];
		for (int j = 0; j < height; j++)
		{
			field_cells[i][j] = f.field_cells[i][j];
		}
	}
	return *this;
}

Field::~Field()
{
	for (int i = 0; i < width; i++)
	{
		delete[](field_cells[i]);
	}
	delete[](field_cells);
}

void Field:: set_new_figure(Figure f) {
	falling_figure = f;
	falling_figure_left_top_point.x = width / 2 - 1;
	falling_figure_left_top_point.y = 0;
}

void Field::set_rotated_figure(Figure f) {
	int tempx = falling_figure_left_top_point.x;
	int tempy =	falling_figure_left_top_point.y;
	falling_figure = f;
	falling_figure_left_top_point.x = tempx;
	falling_figure_left_top_point.y = tempy;
}

Figure Field::get_figure() {
	return falling_figure;
}

void Field::set_previous_figure_state_on_field(array<Coord, 4> _figure_coord) {
	previous_falling_figure_state.set_figure_coord(_figure_coord);
}

Figure Field::get_previous_figure_state() {
	return previous_falling_figure_state;
}

void Field::set_figure_left_top_point(Coord c) {
	falling_figure_left_top_point.x = c.x;
	falling_figure_left_top_point.y = c.y;
}

void Field::set_figure_left_top_point_to_zero() {
	falling_figure_left_top_point.x = width / 2 - 1;
	falling_figure_left_top_point.y = 0;
}

Coord Field::get_figure_left_top_point() {
	return falling_figure_left_top_point;
}

int** Field::get_field_cells() {
	return field_cells;
}

void Field::set_field_cells(int** _field_cells) { // может вместо двумерного массива вставить что-то из STL?
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++) {
			field_cells[i][j] = _field_cells[i][j];
		}	
	}
	//for (int i = 0; i < width; i++)
	//{

	//	for (int j = 0; j < height; j++) {
	//		cout << field_cells[i][j] << ' ';
	//	}
	//	cout << endl;
	//}
	//_getch();
}

int Field::get_cell_value_by_indexes(int i, int j) {
	return field_cells[i][j];
}

void Field::set_cell_value_by_indexes(int value, int i, int j) {
	field_cells[i][j] = value;
}

int Field::get_width() {
	return width;
}
int Field::get_height() {
	return height;
}

Field Field::get_field() {
	return *this;
}

void Field::Falling_figure() {
	falling_figure_left_top_point.y++;
}

void Field::Move_figure_left() {
	falling_figure_left_top_point.x--;
}

void Field::Move_figure_right() {
	falling_figure_left_top_point.x++;
}


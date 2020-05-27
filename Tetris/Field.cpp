#include "Field.h"
#include <iostream>
#include <conio.h>
using namespace std;

using namespace std;

// Field.cpp

// Model


int Field::figure_counterr = 1 ;

Field::Field()
{
//	width = 20;
//	height = 10;
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
	falling_figure_left_top_point.X = width / 2 - 1;
	falling_figure_left_top_point.Y = 0;
}

Field::Field(int _width, int _height)
{
	width = _width;
	height = _height;
	falling_figure_left_top_point.X = width / 2 - 1;
}

Field::Field(const Field& _field)
{
	width = _field.width;
	height = _field.height;

	field_cells = new int*[width];

	for (int i = 0; i < width; i++)
	{
		field_cells[i] = new int[height];
		for (int j = 0; j < height; j++)
		{
			field_cells[i][j] = _field.field_cells[i][j];
		}
	}
    falling_figure_left_top_point.X = _field.falling_figure_left_top_point.X;
	falling_figure_left_top_point.Y = _field.falling_figure_left_top_point.Y;
	falling_figure = _field.falling_figure; 
	next_figure = _field.next_figure;
	previous_falling_figure_state = _field.previous_falling_figure_state;
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
//	cout << endl << figure_counterr++;
	falling_figure.set_figure_alignment(f.get_figure_alignment());
	falling_figure.set_rotation_diff_max_min_XY(f.get_diff(), f.get_maxX(), f.get_maxY(), f.get_minX(), f.get_minY());
	falling_figure_left_top_point.X = width / 2 - 1;
	falling_figure_left_top_point.Y = 0;
}

void Field::set_rotated_figure(Figure f) {
	int tempx = falling_figure_left_top_point.X;
	int tempy =	falling_figure_left_top_point.Y;
	falling_figure.set_figure_alignment(f.get_figure_alignment());
	falling_figure.set_rotation_diff_max_min_XY(f.get_diff(), f.get_maxX(), f.get_maxY(), f.get_minX(), f.get_minY());
	falling_figure_left_top_point.X = tempx;
	falling_figure_left_top_point.Y = tempy;
}

Figure Field::get_figure() {
	return falling_figure;
}

void Field::set_previous_figure_state_on_field(array<COORD, 4> _figure_coord) {
	previous_falling_figure_state.set_figure_alignment(_figure_coord);
}

Figure Field::get_previous_figure_state() {
	return previous_falling_figure_state;
}

void Field::set_figure_left_top_point(COORD c) {
	falling_figure_left_top_point.X = c.X;
	falling_figure_left_top_point.Y = c.Y;
}

const COORD Field::get_figure_left_top_point() {
	return falling_figure_left_top_point;
}

int Field::get_cell_value_by_indexes(int i, int j) {
	return field_cells[i][j];
}

void Field::set_next_figure() {
	next_figure.CreateFigure();
}

Figure Field::get_next_figure() {
	return next_figure;
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

void Field::Move_figure_by_offset(int offset_x, int offset_y) {
	falling_figure_left_top_point.X = falling_figure_left_top_point.X + offset_x;
	falling_figure_left_top_point.Y = falling_figure_left_top_point.Y + offset_y;
}

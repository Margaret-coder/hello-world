#include "Types.h"
#include "Figure.h"
#pragma once

// Field.h

// Model

class Field
{
	int width;
	int height;
	int **field_cells;
	Coord falling_figure_left_top_point; // figure left top point related to field coordinates
	Figure falling_figure;
	Figure previous_falling_figure_state;
	Figure next_figure; // для отображения следующей фигуры справа от поля
public:
	static int figure_counterr;
	Field();
	Field(int _width, int _height);
	Field(const Field& f);
	Field& operator=(Field const& f);
	~Field();
	void set_new_figure(Figure f);
	void set_rotated_figure(Figure f);
	Figure get_figure();
	void set_previous_figure_state_on_field(array<Coord, 4> _figure_coord);
	Figure get_previous_figure_state();
	void set_figure_left_top_point(Coord c);
	const Coord get_figure_left_top_point();
	void set_next_figure();
	Figure get_next_figure();
	void set_cell_value_by_indexes(int value, int i, int j);
	int get_cell_value_by_indexes(int i, int j);
	Field get_field();
	int get_width();
	int get_height();
	void Move_figure_by_offset(int offset_x, int offset_y);
};


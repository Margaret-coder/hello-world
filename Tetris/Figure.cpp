#include "Figure.h"
#include <iostream>
using namespace std;
// Figure.cpp


Figure::Figure()
{
	figure_left_top_point.X = figure_coord[0].X;
	figure_left_top_point.Y = figure_coord[0].Y;
	SetMinMaxCoord();
	shapes = { { "Stick", 1 }, ///явная инициализация map, this map is not in usage yet
	{ "Square", 2 },
	{ "Hook_down", 3 },
	{ "Hook_up", 4 },
	{ "Z_vertical_left", 5 },
	{ "Z_vertical_right", 6 },
	{ "Triple", 7 }
	};
	CreateFigure();
}

Figure:: Figure(const Figure &figure)
{
	figure_coord = figure.figure_coord;
	figure_left_top_point = figure.figure_left_top_point;
	maxx = figure.maxx;
	maxy = figure.maxy;
	minx = figure.minx;
	miny = figure.miny;
	dif = figure.dif;
}

Figure Figure::operator=(const Figure & figure)
{
	if (this == &figure) return *this;
	figure_coord = figure.figure_coord;
	figure_left_top_point = figure.figure_left_top_point;
	maxx = figure.maxx;
	maxy = figure.maxy;
	minx = figure.minx;
	miny = figure.miny;
	dif = figure.dif;
	return *this;
}

Figure::~Figure()
{
}

void Figure::set_figure_alignment(array<COORD, 4> _figure_coord) {
	figure_coord = _figure_coord;
}

array<COORD, 4> Figure::get_figure_alignment() {
	return figure_coord;
}

void Figure::set_figure_left_top_point(COORD ltp)
{
	figure_left_top_point.X = ltp.X;
	figure_left_top_point.Y = ltp.Y;
}

void Figure::set_rotation_diff_max_min_XY(int _diff, int _maxx, int _maxy, int _minx, int _miny)
{
	maxx = _maxx;
	maxy = _maxy;
	minx = _minx;
	miny = _miny;
	dif = _diff;
}



// {{0, 0}, {1, 0}, {2, 0}, {3, 0}} - stick, figure#1 
// {{0, 0}, {1, 0}, {0, 1}, {1, 1}} - square, figure#2 
// {{0, 0}, {1, 0}, {2, 0}, {2, 1}} - Hook_down, figure#3
// {{0, 1}, {1, 1}, {2, 1}, {2, 0}} - Hook_up, figure#4
// {{0, 0}, {0, 1}, {1, 1}, {1, 2}} - Z_vertical_left, figure#5
// {{0, 2}, {0, 1}, {1, 1}, {1, 0}} - Z_vertical_right, figure#6
// {{0, 1}, {1, 0}, {1, 1}, {1, 2}} - Triple, figure#7

void Figure::CreateFigure() {
	srand(time(NULL));
	srand((int)time(0));
	int figure_num = 1 + rand() % (7 - 1);
//	int figure_num = 5 + rand() % (5 - 1); // упрощенный вариант
	switch (figure_num) { // Рандомно выбираем 1 из 7 возможных фигурок
	case 1: figure_coord = { 0, 0, 1, 0, 2, 0, 3, 0 }; break; // stick | 
	case 2: figure_coord = { 0, 0, 1, 0, 0, 1, 1, 1 }; break; // square
	case 3: figure_coord = { 0, 0, 1, 0, 2, 0, 2, 1 }; break; // Г looking downwards
	case 4: figure_coord = { 0, 1, 1, 1, 2, 1, 2, 0 }; break; // reverted Г (upwards)
	case 5: figure_coord = { 0, 0, 0, 1, 1, 1, 1, 2 }; break; // vertical Z
	case 6: figure_coord = { 0, 2, 0, 1, 1, 1, 1, 0 }; break; // reverted vertical Z
	case 7: figure_coord = { 0, 1, 1, 0, 1, 1, 1, 2 }; break; // triple
	}
}


void Figure::SetMinMaxCoord() {
	for (int i = 0; i < figure_coord.size(); i++) {
		if (figure_coord[i].Y > maxy) maxy = figure_coord[i].Y;
		if (figure_coord[i].X > maxx) maxx = figure_coord[i].X;
		if (figure_coord[i].X < minx) minx = figure_coord[i].X;
	}
	dif = minx - figure_left_top_point.X;
}

Figure* Figure::Rotate_figure_up() {
	minx = figure_coord[0].X;
	SetMinMaxCoord();
	if (dif) {
		maxx = 0;
		minx = figure_left_top_point.X;
		for (int i = 0; i < figure_coord.size(); i++)
		{
			figure_coord[i].X = figure_coord[i].X - dif;
			if (figure_coord[i].X > maxx) maxx = figure_coord[i].X;
		}
	}
	for (int i = 0; i < figure_coord.size(); i++) {
		int temp = figure_coord[i].Y;
		figure_coord[i].Y = maxy - (maxx - figure_coord[i].X);
		figure_coord[i].X = maxx + maxy - temp - 1;
	}
	return this;
}

Figure* Figure::Rotate_figure_down() {
	minx = figure_coord[0].X;
	SetMinMaxCoord();
	if (dif) {
		maxy = 0;
		miny = figure_left_top_point.Y;
		for (int i = 0; i < figure_coord.size(); i++)
		{
			figure_coord[i].Y = figure_coord[i].Y - dif;
			if (figure_coord[i].Y > maxy) maxy = figure_coord[i].Y;
		}
	}
	for (int i = 0; i < figure_coord.size(); i++) {
		int temp = figure_coord[i].X;
		figure_coord[i].X = maxx - (maxy - figure_coord[i].Y);
		figure_coord[i].Y = maxy + maxx - temp - 1;
	}
	return this;
}

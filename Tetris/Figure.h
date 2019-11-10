#include <array>
#include <map>
#include <ctime>
#include "Types.h"
#pragma once
using namespace std;

//Figure.h

class Figure
{
	array <Coord, 4> figure_coord;
	Coord figure_left_top_point; // figure_left_top_point - zero coordinates for figure rotation 
//	enum shapes { Stick, Square, Hook_down, Hook_up, Z_vertical_left, Z_vertical_right, Triple }; // DELETE?
	map <string, int> shapes;
	int maxx, maxy, minx, miny, dif;
public:

	Figure();
	Figure(const Figure &figure);
	~Figure();
	array<Coord, 4> get_figure_coord();
	void set_figure_coord(array<Coord, 4> _figure_coord);
	void CreateFigure();
	void SetMinMaxCoord();
	Figure* Rotate_figure_up();
	Figure* Rotate_figure_down();
};


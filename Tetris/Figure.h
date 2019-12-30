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
	const int figure_fraction_size = 4;
	int maxx, maxy, minx, miny, dif;
public:
	Figure();
	Figure(const Figure &figure);
	Figure operator= (const Figure &figure);
	~Figure();
	void set_figure_coord(array<Coord, 4> _figure_coord);
	array<Coord, 4> get_figure_coord();
	void set_figure_left_top_point(Coord ltp);
	Coord get_figure_left_top_point() { return figure_left_top_point; }
	const int get_figure_fraction_size();
	void set_maxX(int _maxx);
	void set_maxY(int _maxy);
	void set_minX(int _minx);
	void set_minY(int _miny);
	void set_diff(int _dif);
	int get_maxX() { return maxx; }
	int get_maxY() { return maxy; }
	int get_minX() { return minx; }
	int get_minY() { return miny; }
	int get_diff() { return dif; }
	void CreateFigure();
	void SetMinMaxCoord();
	Figure* Rotate_figure_up();
	Figure* Rotate_figure_down();
};


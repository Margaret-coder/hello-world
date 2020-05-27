#include <array>
#include <map>
#include <ctime>
#include <windows.h>
#include "Types.h"
#pragma once
using namespace std;

//Figure.h

class Figure
{
	array <COORD, 4> figure_coord;
	COORD figure_left_top_point; // figure_left_top_point - zero coordinates for figure rotation 
//	enum shapes { Stick, Square, Hook_down, Hook_up, Z_vertical_left, Z_vertical_right, Triple }; // DELETE?
	map <string, int> shapes;
	int maxx, maxy, minx, miny, dif;
public:
	Figure();
	Figure(const Figure &figure);
	Figure operator= (const Figure &figure);
	~Figure();
	void set_figure_alignment(array<COORD, 4> _figure_coord);
	array<COORD, 4> get_figure_alignment();
	void set_figure_left_top_point(COORD ltp);
	COORD get_figure_left_top_point() { return figure_left_top_point; }
	void set_rotation_diff_max_min_XY(int _diff, int _maxx, int _maxy, int _minx, int _miny);
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


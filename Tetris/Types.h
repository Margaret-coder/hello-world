#pragma once
#include<string>
#include<vector>

struct Coord {
	int x;
	int y;
};

enum class actions : int { 
	UP = 72, 
	LEFT = 75, 
	RIGHT = 77, 
	DOWN = 80,
	MIN = 0,
	MAX = 224
};



/*enum class actions : int {
UP,
LEFT,
RIGHT,
DOWN,
MIN,
MAX
};*/

struct Field_cells
{
private:
	int **field_cells;
	int width;
	int height;
	Field_cells() {
		field_cells = new int*[width];
		for (int i = 0; i < width; i++)
		{
			field_cells[i] = new int[height];
			for (int j = 0; j < height; j++) {
				field_cells[i][j] = 0;
			}
		}
	}

	void set_field_cells(const Field_cells& f) {
		for (int i = 0; i < f.width; i++)
		{
			for (int j = 0; j < f.height; j++)
			{
				field_cells[i][j] = f.field_cells[i][j];
			}
		}
    }

	int** get_field_cells() {
		return field_cells;
	}

	~Field_cells() {
		for (int i = 0; i < width; i++)
		{
			delete[](field_cells[i]);
		}
		delete[](field_cells);
	}
};
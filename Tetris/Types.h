#pragma once
#include<string>

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
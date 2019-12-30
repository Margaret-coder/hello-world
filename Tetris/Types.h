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

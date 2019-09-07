#include "Field.h"
#include "Figure.h"
#include "View.h"
#include "Timer.h"
#include "Types.h"
#pragma once

class Game
{
	Field game_field;
	View view;
	Figure figure;
	int temp_time;
	char const *  action;
	Timer timer;
public:
	void set_field(Field _game_field);
	Field get_field();
	Game();
	~Game();
	bool Is_falling_figure_collision();
	void Place_figure();
	void Remove_previous_figure_state();
	void Set_figure_as_a_field_part();
	void StartGame();
};


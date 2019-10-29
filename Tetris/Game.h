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
	int score;
	bool Is_falling_figure_collision(int offset_x, int offset_y);
	bool Game::Is_falling_figure_collision_diagonal(int offset_x, int offset_y);
	bool Is_falling_figure_collision_by_side_only(int offset_x);
	void Place_figure();
	void Remove_previous_figure_state();
	void Set_figure_as_a_field_part();
	int Field_check_full_row_index();
	void Erase_complete_row(int index);
public:
	void set_field(Field _game_field);
	Field get_field();
	Game();
	~Game();
	void Update_field();
	void StartGame();
};


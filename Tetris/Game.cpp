#include "Game.h"

using namespace std;

Game::Game() : game_field(), timer()
{
	srand(time(NULL));
	srand((int)time(0));
	temp_time = 0;
}

Game::~Game()
{
}

void Game::set_field(Field _game_field) {
	game_field = _game_field;
}

Field Game::get_field() {
	return game_field;
}

bool Game::Is_falling_figure_collision() {
	Coord figure_point;
	array<Coord, 4>  temp_figure_coord = game_field.get_figure().get_figure_coord();
	for (int k = 0; k < temp_figure_coord.size(); k++) {
		for (int i = 0; i < game_field.get_width(); i++)
		{
			for (int j = 0; j < game_field.get_height(); j++)
			{
				figure_point.y = temp_figure_coord[k].y + game_field.get_figure_left_top_point().y;
				figure_point.x = temp_figure_coord[k].x + game_field.get_figure_left_top_point().x;
				if (figure_point.y + 1 == game_field.get_height())
					{
						return true;
					}
				else if (((figure_point.y + 1) == j)
					&& (game_field.get_cell_value_by_indexes(figure_point.x, figure_point.y + 1) == 2)) // МАГИЧЕСКОЕ ЧИСЛО 2 (и 1 тоже надо оформить)
				{
					return true;
				}			
			}
		}
	}
	return false;
}


// places figure on the field and saves previous figure state
void Game::Place_figure() { 
	array <Coord, 4> figure_coord = game_field.get_figure().get_figure_coord();
	array <Coord, 4> temp_figure_on_field_state = figure_coord;
	Coord left_top_point = game_field.get_figure_left_top_point();

	for (int i = 0; i < game_field.get_width(); i++)
	{
		for (int j = 0; j < game_field.get_height(); j++)
		{
			for (int k = 0; k < figure_coord.size(); k++)
			{ 
				if (((figure_coord[k].x + left_top_point.x) == i) && ((figure_coord[k].y + left_top_point.y) == j)
					&& (game_field.get_cell_value_by_indexes(i, j) != 2)) // 2 - это наваленные  в поле фигуры
				{			
						game_field.set_cell_value_by_indexes(1, i, j);
						temp_figure_on_field_state[k].x = i;
						temp_figure_on_field_state[k].y = j;
				}		
			}
		}
	}
	game_field.set_previous_figure_state_on_field(temp_figure_on_field_state);
	}


void Game::Remove_previous_figure_state() { 
	array <Coord, 4> temp_figure_on_field_state = game_field.get_previous_figure_state().get_figure_coord();
	for (int k = 0; k < temp_figure_on_field_state.size(); k++) {
		for (int i = 0; i < game_field.get_width(); i++)
		{
			for (int j = 0; j < game_field.get_height(); j++) {
				if (temp_figure_on_field_state[k].x == i && temp_figure_on_field_state[k].y == j)
				{
					game_field.set_cell_value_by_indexes(0, i, j);
				}
			}
		}
	}
}

void Game::Set_figure_as_a_field_part() {
	array <Coord, 4> figure_coord = game_field.get_figure().get_figure_coord();
	array <Coord, 4> temp_figure_on_field_state = figure_coord;
	Coord left_top_point = game_field.get_figure_left_top_point();
	for (int i = 0; i < game_field.get_width(); i++)
	{
		for (int j = 0; j < game_field.get_height(); j++)
		{
			for (int k = 0; k < figure_coord.size(); k++)
			{
				if (((figure_coord[k].x + left_top_point.x) == i) && ((figure_coord[k].y + left_top_point.y) == j)
					&& (game_field.get_cell_value_by_indexes(i, j) == 1))
				{
					game_field.set_cell_value_by_indexes(2, i, j); // изменяем значение поля на 2, это наваленные фигуры
				}
			}
		}
	}
}

void Game::StartGame() {
	std::string EnumStrings[6] = { "UP", "LEFT", "RIGHT", "DOWN", "MIN", "MAX" };
	View view(game_field);
	view.DrawField(game_field);
	while (1)
	{
		int** game_field_cells;
		game_field_cells = new int*[game_field.get_width()];
		for (int i = 0; i < game_field.get_width(); i++)
		{
			game_field_cells[i] = new int[game_field.get_height()];
			for (int j = 0; j < game_field.get_height(); j++) {
				game_field_cells[i][j] = game_field.get_field_cells()[i][j];
			}
		}

		if(timer.Elapsed().count() - temp_time > 0){
			int max_y = game_field.get_figure_left_top_point().y;
			array<Coord, 4>  temp_figure_coord = game_field.get_figure().get_figure_coord();
			for (int i = 0; i < temp_figure_coord.size(); i++) {
				if ((temp_figure_coord[i].y + game_field.get_figure_left_top_point().y) > max_y) {
					max_y = temp_figure_coord[i].y + game_field.get_figure_left_top_point().y;
				}
			}
			
		temp_time = timer.Elapsed().count();
		action = view.ViewAction(game_field);
		if (strlen(action) > 1 ) {
			// перемещения координат фигуры в поле по keyboard interaction
			if (!strcmp(action, "UP")) { 
				game_field.set_rotated_figure(*game_field.get_figure().Rotate_figure_up());
			}
			else if (!strcmp(action, "LEFT")) { 
				if (game_field.get_figure_left_top_point().x > 1)	game_field.Move_figure_left();
			}
			else if (!strcmp(action, "RIGHT")) { 
				view.DrawField(game_field);
				int max_x = game_field.get_figure_left_top_point().x;
				array<Coord, 4>  temp_figure_coord = game_field.get_figure().get_figure_coord();
				for (int i = 0; i < temp_figure_coord.size(); i++) {
					if ((temp_figure_coord[i].x + game_field.get_figure_left_top_point().x) > max_x) {
						max_x = temp_figure_coord[i].x + game_field.get_figure_left_top_point().x;
					}
				}
				if (max_x < game_field.get_width() - 2) {
					game_field.Move_figure_right();
				}
			}
			else if (!strcmp(action, "DOWN")) { 
				game_field.set_rotated_figure(*game_field.get_figure().Rotate_figure_down());				
			}
		}

		// падение фигуры
		if (Is_falling_figure_collision() == false) {
				game_field.Falling_figure(); // change figure coordinates by Y
				Remove_previous_figure_state();
			}
		// set figure as a field part by not removing it's previous state
		else {
			Set_figure_as_a_field_part();
			figure.CreateFigure();
			game_field.set_new_figure(figure);
		}
		Place_figure();
		view.DrawField(game_field);
	}
	}
}



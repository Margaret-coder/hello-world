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

// создать Git репозиторий
// фигура может цепляться любой точкой, поэтому максимальную нет смысла проверять (cтранно, но без максимальной не работает), 
//надо проверять все подряд. В некоторых случаях фигура пролетает. В фигуре выставлены трипл и зэт рандомно. Отдебажить на них
//bool Game::Is_falling_figure_collision() { 
//	Coord max_y_point = game_field.get_figure_left_top_point();
//	array<Coord, 4>  temp_figure_coord = game_field.get_figure().get_figure_coord();
//	for (int i = 0; i < game_field.get_width(); i++)
//	{
//		for (int j = 0; j < game_field.get_height(); j++)
//		{
//			for (int k = 0; k < temp_figure_coord.size(); k++) {
//				if ((temp_figure_coord[k].y + game_field.get_figure_left_top_point().y) >= max_y_point.y) {
//					max_y_point.y = temp_figure_coord[k].y + game_field.get_figure_left_top_point().y;
//					max_y_point.x = temp_figure_coord[k].x + game_field.get_figure_left_top_point().x;
//					cout << endl << max_y_point.x << " " << max_y_point.y;
//					
//					if (max_y_point.y + 1 == game_field.get_height())
//					{
//						return true;
//					}
//					else if (((max_y_point.y + 1) == j)
//						&& (game_field.get_cell_value_by_indexes(max_y_point.x, max_y_point.y + 1) == 1))
//					{
//						return true;
//					}					
//				}
//			}
//		}	
//	} 
//	return false;
//}

bool Game::Is_falling_figure_collision() { // не работает, падает хз чего
	array <Coord, 4> figure_coord = game_field.get_figure().get_figure_coord();
	array <Coord, 4> temp_figure_on_field_state;
	Coord left_top_point = game_field.get_figure_left_top_point();
	int counter = Figure::counterr;
	for (int i = 0; i < game_field.get_width(); i++)
	{
		for (int j = 0; j < game_field.get_height(); j++)
		{
			for (int k = 0; k < figure_coord.size(); k++)
			{
				if (figure_coord[k].y + left_top_point.y + 1 == game_field.get_height())
				{
					return true;
				}
				else if (((figure_coord[k].x + left_top_point.x) == i) && (figure_coord[k].y + left_top_point.y + 1) == j)
				{
					for (int l = 0; l < figure_coord.size(); l++)
					{
						if (figure_coord[k].x == figure_coord[l].x && figure_coord[k].y + 1 == figure_coord[l].y)
						{
				//			cout << endl << Figure::counter;//	return true;
						}
						else if (game_field.get_cell_value_by_indexes(i, j) == 1) {
						//	return true;
						}
					}
				//	cout << "OK";
					
				//	return true;
				}
			}
		}
	}
	return false;
}

void Game::Place_figure() { 
	array <Coord, 4> figure_coord = game_field.get_figure().get_figure_coord();
	array <Coord, 4> temp_figure_on_field_state;
	Coord left_top_point = game_field.get_figure_left_top_point();

	for (int i = 0; i < game_field.get_width(); i++)
	{
		for (int j = 0; j < game_field.get_height(); j++)
		{
			for (int k = 0; k < figure_coord.size(); k++)
			{ 
				if (((figure_coord[k].x + left_top_point.x) == i) && ((figure_coord[k].y + left_top_point.y) == j)
					&& (game_field.get_cell_value_by_indexes(i, j) != 1))
				{			
						game_field.set_cell_value_by_indexes(1, i, j);
						temp_figure_on_field_state[k].x = i;
						temp_figure_on_field_state[k].y = j;
				}		
			/*	else if (((figure_coord[k].x + left_top_point.x) == i) && ((figure_coord[k].y + left_top_point.y) == j)
					&& (game_field.get_cell_value_by_indexes(i, j) == 1))
				{
					figure_coord[k].x = temp_figure_on_field_state[k].x - left_top_point.x;
					figure_coord[k].y = temp_figure_on_field_state[k].y - left_top_point.y;
					return;
				}*/
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
		//	if (max_y < game_field.get_height() - 1) {
			if (Is_falling_figure_collision() == false){
				game_field.Falling_figure(); // another condition related to field configuration
				Remove_previous_figure_state();
				int** game_field_cells;
				game_field_cells = new int*[game_field.get_width()];
				for (int i = 0; i < game_field.get_width(); i++)
				{
					game_field_cells[i] = new int[game_field.get_height()];
					for (int j = 0; j < game_field.get_height(); j++) {
						game_field_cells[i][j] = game_field.get_field_cells()[i][j];
					}
				}
			}
			// set figure as a field part by not removing it's previous state
			else { 
				int** game_field_cells;
				game_field_cells = new int*[game_field.get_width()];
				for (int i = 0; i < game_field.get_width(); i++)
				{
					game_field_cells[i] = new int[game_field.get_height()];
					for (int j = 0; j < game_field.get_height(); j++) {
						game_field_cells[i][j] = game_field.get_field_cells()[i][j];
					}
				}
		
				figure.CreateFigure();
				
				game_field.set_new_figure(figure);
				
			}
		temp_time = timer.Elapsed().count();
		action = view.ViewAction(game_field);
		if (strlen(action) > 1 ) {
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

		Place_figure();
		
		view.DrawField(game_field);
	}
	}
}



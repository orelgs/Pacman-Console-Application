#include "../Header/Pacman.h"

Pacman::Pacman(const Point& start_location, const int& pacman_start_score, const int& pacman_start_lives)
{
	_lives = pacman_start_lives;
	_points = pacman_start_score;
	setSign('@');
	setStartLocation(start_location);
}

void Pacman::move(Board& board, GameDetails& game_details)
{
	if (game_details.getGameMode() == GameMode::LOAD || game_details.getGameMode() == GameMode::SILENT)
	{
		char direction;
		game_details.getStepsFile()->get(direction);
		setDirection((Direction)direction);
		char cur_line[30];
		game_details.getStepsFile()->getline(cur_line, 29, '\n');
	}
	
	Point next_pacman_location = getNextLocation();

	if (board.isTunnel(next_pacman_location))
		next_pacman_location = board.tunnelExit(next_pacman_location);
	if (board.isInBoardBounds(next_pacman_location) && !board.isWall(next_pacman_location))
		setCurLocation(next_pacman_location);
	if (board.isBreadcrumb(getCurLocation())) {
		eatBreadcrumb();
		board.setBreadcrumb(getCurLocation(), false);
	}
	
	increaseMoveCount();
}
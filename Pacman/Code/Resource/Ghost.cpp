#include "../Header/Ghost.h"

Ghost::Ghost(const Point& start_location, const Difficulty& difficulty)
{
	setSign('$');
	setStartLocation(start_location);
	_difficulty = difficulty;
	random_num = rand() % 4;
}

void Ghost::move(Board& board, GameDetails& game_details)
{
	if (game_details.getGameMode() != GameMode::LOAD && game_details.getGameMode() != GameMode::SILENT)
	{
		checkAvailableDirections(board);

		switch (_difficulty)
		{
		case Difficulty::NOVICE:
			moveNoviceGhost(board);
			break;
		case Difficulty::GOOD:
			moveGoodGhost(board);
			break;
		case Difficulty::BEST:
			moveBestGhost(board);
			break;
		}
	}
	else
	{
		char direction;
		game_details.getStepsFile()->get(direction);
		setDirection((Direction)direction);
		setCurLocation(getNextLocation());
		char cur_line[30];
		game_details.getStepsFile()->getline(cur_line, 29, '\n');
	}
	increaseMoveCount();
}

void Ghost::moveNoviceGhost(const Board& board)
{
	bool valid_direction = true;
	Point next_ghost_location = getNextLocation();

	do
	{
		if (getMovesCount() % 19 == 0 || !valid_direction || getDirection() == Direction::STAY)
		{
			setDirection(available_directions[rand() % available_directions.size()]);
			next_ghost_location = getNextLocation();
			resetMoveCount();
		}
		if (isValidLocation(board, next_ghost_location))
		{
			valid_direction = true;
			setCurLocation(next_ghost_location);
		}
		else
			valid_direction = false;
	} while (!valid_direction);
}

void Ghost::moveGoodGhost(const Board& board)
{
	bool valid_direction = false;
	Point next_ghost_location = getNextLocation();

	if (getMovesCount() == 22 + random_num)
	{
		resetMoveCount();
		random_num = rand() % 4;
	}

	if (getMovesCount() < 17 + random_num)
		moveBestGhost(board);
	else
	{
		if (getMovesCount() == 17 + random_num || getDirection() == Direction::STAY)
			setDirection(available_directions[rand() % available_directions.size()]);
			
		if (isValidLocation(board, next_ghost_location))
			setCurLocation(getNextLocation());
	}
}

void Ghost::moveBestGhost(const Board& board)
{
	Point pacman_location = board.getEntitiesLocations()[0], ghost_location = getCurLocation();
	vector<Direction> direction_towards_pacman;

	if (ghost_location.getX() < pacman_location.getX() && std::find(available_directions.begin(), available_directions.end(), Direction::RIGHT) != available_directions.end())
		direction_towards_pacman.push_back(Direction::RIGHT);
	if (ghost_location.getX() > pacman_location.getX() && std::find(available_directions.begin(), available_directions.end(), Direction::LEFT) != available_directions.end())
		direction_towards_pacman.push_back(Direction::LEFT);
	if (ghost_location.getY() < pacman_location.getY() && std::find(available_directions.begin(), available_directions.end(), Direction::DOWN) != available_directions.end())
		direction_towards_pacman.push_back(Direction::DOWN);
	if (ghost_location.getY() > pacman_location.getY() && std::find(available_directions.begin(), available_directions.end(), Direction::UP) != available_directions.end())
		direction_towards_pacman.push_back(Direction::UP);

	if (direction_towards_pacman.empty())
		setDirection(available_directions[rand() % available_directions.size()]);
	else
		setDirection(direction_towards_pacman[rand() % direction_towards_pacman.size()]);

	setCurLocation(getNextLocation());
}

bool Ghost::isValidLocation(const Board& board, const Point& location) const
{
	bool res = true;

	vector<Point> entities_locations = board.getEntitiesLocations();

	if (!board.isInBoardBounds(location) || board.isTunnel(location) || board.isWall(location))
		res = false;
	if (std::find(entities_locations.begin() + 1, entities_locations.end(), location) != entities_locations.end())
	{
		if (!location.isEqual(getCurLocation()))
			res = false;
	}
	return res;
}

void Ghost::checkAvailableDirections(const Board& board)
{
	Point ghost_location = getCurLocation();
	available_directions.clear();

	if (isValidLocation(board, Point(ghost_location.getX(), ghost_location.getY() - 1)))
		available_directions.push_back(Direction::UP);
	if (isValidLocation(board, Point(ghost_location.getX(), ghost_location.getY() + 1)))
		available_directions.push_back(Direction::DOWN);
	if (isValidLocation(board, Point(ghost_location.getX() - 1, ghost_location.getY())))
		available_directions.push_back(Direction::LEFT);
	if (isValidLocation(board, Point(ghost_location.getX() + 1, ghost_location.getY())))
		available_directions.push_back(Direction::RIGHT);

	if (available_directions.empty())
		available_directions.push_back(Direction::STAY);
}
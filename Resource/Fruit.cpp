#include "../Header/Fruit.h"

Fruit::Fruit()
{
	_time_dead = _time_alive = 0;
	_alive = false;
	random_num = rand() % 9;
}

void Fruit::init(const Board& board)
{
	generateRandomValue();
	setStartLocation(board.getEmptySpace());
	_time_dead = _time_alive = 0;
	_alive = true;
	setDirection(Direction::STAY);
}

void Fruit::kill(const Board& board, const GameMode& mode)
{
	if (isAlive() && mode != GameMode::SILENT)
	{
		board.displaySingleCoordinate(getCurLocation());
		board.displaySingleCoordinate(getPrevLocation());
	}
	_time_dead = _time_alive = _value = 0;
	_alive = false;
	random_num = rand() % 9;
	
}

void Fruit::movement(const Board& board)
{
	int arr_log_size = 0;
	Direction available_directions[4];
	Point fruit_location = getCurLocation();

	if (board.isInBoardBounds(Point(fruit_location.getX(), fruit_location.getY() - 1)) && !board.isTunnel(Point(fruit_location.getX(), fruit_location.getY() - 1)) && !board.isWall(Point(fruit_location.getX(), fruit_location.getY() - 1))) {
		available_directions[arr_log_size] = Direction::UP;
		arr_log_size++;
	}
	if (board.isInBoardBounds(Point(fruit_location.getX(), fruit_location.getY() + 1)) && !board.isTunnel(Point(fruit_location.getX(), fruit_location.getY() + 1)) && !board.isWall(Point(fruit_location.getX(), fruit_location.getY() + 1))) {
		available_directions[arr_log_size] = Direction::DOWN;
		arr_log_size++;
	}
	if (board.isInBoardBounds(Point(fruit_location.getX() - 1, fruit_location.getY())) && !board.isTunnel(Point(fruit_location.getX() - 1, fruit_location.getY())) && !board.isWall(Point(fruit_location.getX() - 1, fruit_location.getY()))) {
		available_directions[arr_log_size] = Direction::LEFT;
		arr_log_size++;
	}
	if (board.isInBoardBounds(Point(fruit_location.getX() + 1, fruit_location.getY())) && !board.isTunnel(Point(fruit_location.getX() + 1, fruit_location.getY())) && !board.isWall(Point(fruit_location.getX() + 1, fruit_location.getY()))) {
		available_directions[arr_log_size] = Direction::RIGHT;
		arr_log_size++;
	}

	setDirection(available_directions[rand() % arr_log_size]);

	setCurLocation(getNextLocation());
}

void Fruit::move(Board& board, GameDetails& game_details)
{
	if (game_details.getGameMode() != GameMode::LOAD && game_details.getGameMode() != GameMode::SILENT)
	{
		if (!_alive)
		{
			if (_time_dead == 6 + random_num)
			{
				init(board);
				if (game_details.getGameMode() == GameMode::SAVE)
					*(game_details.getStepsFile()) << "1 S " << getCurLocation().getX() << " " << getCurLocation().getY() << " " << getValue() << endl;
			}
			else
				_time_dead++;
		}
		else
		{
			if (_time_alive == 9)
			{
				kill(board, game_details.getGameMode());
				if (game_details.getGameMode() == GameMode::SAVE)
					*(game_details.getStepsFile()) << "1 -" << endl;
				board.displaySingleCoordinate(getCurLocation());
			}
			else
			{
				_time_alive++;
				movement(board);
			}
		}
	}
	else
	{
		char direction;
		game_details.getStepsFile()->get(direction);

		if (direction == '-')
		{
			kill(board, game_details.getGameMode());
			if (game_details.getGameMode() == GameMode::LOAD)
				board.displaySingleCoordinate(getCurLocation());
			char cur_line[30];
			game_details.getStepsFile()->getline(cur_line, 29, '\n');
		}
		else if ((Direction)direction == Direction::STAY)
		{
			char cur_line[30];
			game_details.getStepsFile()->getline(cur_line, 29, '\n');
			std::stringstream sstream(cur_line);
			int x, y, value;
			_alive = true;
			sstream >> x >> y >> value;
			setStartLocation(Point(x, y));
			_value = value;
			setSign(_value + '0');
			setDirection(Direction::STAY);
		}
		else
		{
			setDirection((Direction)direction);
			char cur_line[30];
			game_details.getStepsFile()->getline(cur_line, 29, '\n');
			setCurLocation(getNextLocation());
		}
	}
}
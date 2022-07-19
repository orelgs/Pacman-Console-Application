#include "../Header/Board.h"

Board::Board(const vector<string>& boards) : _walls(boards[0].size(), boards.size()), _breadcrumbs(boards[0].size(), boards.size())
{
	_board_width = boards[0].size();
	_board_height = boards.size();
	_breadcrumbs_on_board = 0;

	for (int i = 0; i < _board_width; i++) {
		for (int j = 0; j < _board_height; j++) {
			Point coordinate = Point(i, j);
			if (boards[j][i] == '#')
				_walls.setWall(coordinate);
			if (boards[j][i] == '.') {
				_breadcrumbs.setBreadcrumb(coordinate);
				_breadcrumbs_on_board++;
			}
			if (boards[j][i] == '@')
				_pacman_start_location = coordinate;
			if (boards[j][i] == '$')
				_ghost_start_locations.push_back(coordinate);
			if (boards[j][i] == '&')
				_scoreboard_location = coordinate;
		}
	}
}

void Board::displayWallsAndBreadcrumbs() const
{
	for (int i = 0; i < _board_width; i++) {
		for (int j = 0; j < _board_height; j++) {
			Utility().gotoxy(i, j);
			if (isWall(Point(i, j)))
			{
				if (colours) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::BLUE | 0x00FF | 0x0015);
				cout << '#';
			}
			else if (isBreadcrumb(Point(i, j)))
			{
				if (colours) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::LIGHTYELLOW);
				cout << '.';
			}
			else
			{
				if (colours) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::LIGHTGREY);
				cout << ' ';
			}
		}
	}
}

bool Board::isTunnel(const Point& location) const
{
	bool res = false;
	if (location.getX() < 0 && isInBoardBounds(Point(_board_width - 1, location.getY())) && !_walls.isWall(Point(_board_width - 1, location.getY())))
		res = true;
	else if (location.getX() > _board_width - 1 && isInBoardBounds(Point(0, location.getY())) && !_walls.isWall(Point(0, location.getY())))
		res = true;
	else if (location.getY() < 0 && isInBoardBounds(Point(location.getX(), _board_height - 1)) && !_walls.isWall(Point(location.getX(), _board_height - 1)))
		res = true;
	else if (location.getY() > _board_height - 1 && isInBoardBounds(Point(location.getX(), 0)) && !_walls.isWall(Point(location.getX(), 0)))
		res = true;

	return res;
}

Point Board::tunnelExit(const Point& location) const
{
	Point exit = location;

	if (location.getX() < 0)
		exit.setX(_board_width - 1);
	else if (location.getX() > _board_width - 1)
		exit.setX(0);
	if (location.getY() < 0)
		exit.setY(_board_height - 1);
	else if (location.getY() > _board_height - 1)
		exit.setY(0);

	return exit;
}

void Board::updateEntitiesLocations(const vector<Point>& entities_locations)
{
	int i = 0;

	if (_entities_locations.empty())
	{
		for (auto it = entities_locations.begin(); it != entities_locations.end(); it++)
			_entities_locations.push_back(*it);
	}
	else
	{
		for (auto it = _entities_locations.begin(); it != _entities_locations.end(); it++, i++)
			*it = entities_locations[i];
	}
}

bool Board::isLocationEmpty(const Point& location) const
{
	for (auto it = _entities_locations.begin(); it != _entities_locations.end(); it++)
	{
		if (location.isEqual(*it))
			return false;
	}
	return !isWall(location);
}

bool Board::isLocationOnScoreboard(const Point& location) const
{
	return location.getX() >= _scoreboard_location.getX() && location.getX() <= _scoreboard_location.getX() + 19 && location.getY() >= _scoreboard_location.getY() && location.getY() <= _scoreboard_location.getY() + 2;
}

Point Board::getEmptySpace() const
{
	bool is_valid_location = false;
	Point location;

	while (!is_valid_location) {
		location.setX(rand() % getBoardWidth());
		location.setY(rand() % getBoardHeight());

		if (isLocationEmpty(location) && !isLocationOnScoreboard(location))
			is_valid_location = true;
	}

	return location;
}

void Board::displaySingleCoordinate(const Point& location) const
{
	char char_to_display;
	Utility().gotoxy(location.getX(), location.getY());
	if (isBreadcrumb(location))
		char_to_display = '.';
	else
		char_to_display = ' ';

	if (colours) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::LIGHTYELLOW);
	cout << char_to_display;
}
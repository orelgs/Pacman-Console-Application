#ifndef BOARD_H
#define BOARD_H

#include "Walls.h"
#include "Breadcrumbs.h"
#include "Utility.h"

enum class BoardSizes
{
	SMALL_BOARD_WIDTH = 51,
	SMALL_BOARD_HEIGHT = 13,
	BIG_BOARD_WIDTH = 71,
	BIG_BOARD_HEIGHT = 21
};

class Board
{
private:
	int _board_width, _board_height, _breadcrumbs_on_board;
	bool colours;
	Walls _walls;
	Breadcrumbs _breadcrumbs;
	Point _pacman_start_location, _scoreboard_location;
	vector<Point> _entities_locations;
	vector<Point> _ghost_start_locations;

public:
	Board(const vector<string>& boards);

	const Point& getPacmanStartLocation() const
	{
		return _pacman_start_location;
	}

	const vector<Point>& getGhostStartLocations() const
	{
		return _ghost_start_locations;
	}

	const Point& getScoreboardLocation() const
	{
		return _scoreboard_location;
	}

	const int& getBoardWidth() const
	{
		return _board_width;
	}

	const int& getBoardHeight() const
	{
		return _board_height;
	}

	/**************************[getEmptySpace]**************************
	This function returns an empty space on the board - without walls
	or entities.
	Output:
	-Point - an empty location.
	*******************************************************************/
	Point getEmptySpace() const;

	const vector<Point>& getEntitiesLocations() const
	{
		return _entities_locations;
	}

	const int& getBreadcrumbsOnBoard() const
	{
		return _breadcrumbs_on_board;
	}

	/************************[isWall]***************************
	This function checks if there's a wall in current location.
	Input:
	-const Point& location - location to check, by reference.
	***********************************************************/
	bool isWall(const Point& location) const
	{
		return _walls.isWall(location);
	}

	/**************************[isTunnel]****************************
	This function checks if the location received is a tunnel.
	Input:
	-const Point& location - location to check.
	****************************************************************/
	bool isTunnel(const Point& location) const;

	bool isBreadcrumb(const Point& location) const
	{
		return _breadcrumbs.isBreadcrumb(location);
	}

	/*******************[isInBoardBounds]**********************
	This function checks if a location is in board bounds.
	Input:
	-const Point& location - location to check, by reference.
	**********************************************************/
	bool isInBoardBounds(const Point& location) const
	{
		return location.getX() >= 0 && location.getX() <= _board_width - 1 && location.getY() >= 0 && location.getY() <= _board_height - 1;
	}

	/****************[isLocationOnScoreboard]*******************
	This function checks if location recieved is on scoreboard.
	Input:
	-const Point& location - location to check, by reference.
	***********************************************************/
	bool isLocationOnScoreboard(const Point& location) const;

	/**************************[isLocationEmpty]**************************
	This function checks if the received location has a wall or entity.
	Input:
	-const Point& location - the location to check.
	Output:
	-true - if location is empty.
	-false - else.
	*********************************************************************/
	bool isLocationEmpty(const Point& location) const;

	void setColours(const bool& value)
	{
		colours = value;
	}

	/**************************[setWall]**************************
	This function sets a wall in current location in walls layout.
	Input:
	-const Point& location - location to update, by reference.
	-const bool& value = true - default value.
	*************************************************************/
	void setWall(const Point& location, const bool& value = true)
	{
		_walls.setWall(location, value);
	}

	/**************************[setBreadcrumb]**************************
	This function sets a breadcrumb in current location in breadcrumbs
	layout.
	Input:
	-const Point& location - location to update, by reference.
	-const bool& value = true - default value.
	*******************************************************************/
	void setBreadcrumb(const Point& location, const bool& value = true)
	{
		_breadcrumbs.setBreadcrumb(location, value);
	}

	/************************[updateEntitiesLocations]***************************
	This function updates the entities locations vector.
	Input:
	-const vector<Point>& entities_locations - a vector of the entities'
	locations.
	****************************************************************************/
	void updateEntitiesLocations(const vector<Point>& entities_locations);

	/**************************[tunnelExit]****************************
	This function returns the exit of the tunnel received.
	Input:
	-const Point& location - location of tunnel entrance.
	Output:
	-Point - location of tunnel exit.
	******************************************************************/
	Point tunnelExit(const Point& location) const;

	/***********************[displaySingleCoordinate]************************
	This function displays an entity's previous location.
	Input:
	-const Point& location - location to display.
	************************************************************************/
	void displaySingleCoordinate(const Point& location) const;

	/*******************[displayWallsAndBreadcrumbs]*********************
	This function prints the walls and breadcrumbs during the game.
	********************************************************************/
	void displayWallsAndBreadcrumbs() const;
};

#endif
#ifndef WALLS_H
#define WALLS_H

#include "Point.h"

class Walls
{
private:
	int _board_width, _board_height;
	bool** _layout;

public:
	Walls(const int& board_width, const int& board_height);

	Walls(const Walls& w) = delete;

	Walls& operator=(const Walls& w) = delete;

	/******************************[isWall]*******************************
	This function checks if there is a wall in given location.
	Input:
	-Point location - location to check
	Output:
	true if there is a wall, false otherwise.
	*********************************************************************/
	const bool& isWall(const Point& location) const
	{
		return _layout[location.getX()][location.getY()];
	}

	/**************************[setWall]**************************
	This function sets a wall in current location in walls layout.
	Input:
	-const Point& location - location to update, by reference.
	-const bool& value = true - default value.
	*************************************************************/
	void setWall(const Point& location, const bool& value = true)
	{
		_layout[location.getX()][location.getY()] = value;
	}

	~Walls();
};

#endif
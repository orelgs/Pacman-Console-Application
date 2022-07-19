#ifndef ENTITY_H
#define ENTITY_H

#include "Point.h"
#include "Utility.h"
#include "Board.h"
#include "GameDetails.h"

enum class Direction
{
	UP = 'W',
	DOWN = 'X',
	LEFT = 'A',
	RIGHT = 'D',
	STAY = 'S',
	ESC = 27
};

class Entity
{
private:
	Point _prev_location, _cur_location, _start_location;
	char _sign;
	int _moves_counter = 0;
	Direction _direction = Direction::STAY;

protected:
	void increaseMoveCount()
	{
		_moves_counter++;
	}

public:
	void resetMoveCount()
	{
		_moves_counter = 0;
	}

	const Point& getCurLocation() const
	{
		return _cur_location;
	}

	const Point& getPrevLocation() const
	{
		return _prev_location;
	}

	const int& getMovesCount() const
	{
		return _moves_counter;
	}

	void setSign(const char& sign)
	{
		_sign = sign;
	}

	void setDirection(const Direction& direction)
	{
		_direction = direction;
	}

	const Direction& getDirection() const
	{
		return _direction;
	}

	void setStartLocation(const Point& location)
	{
		_start_location = _prev_location = _cur_location = location;
	}

	const Point& getStartLocation() const
	{
		return _start_location;
	}

	/*************************[getNextLocation]*****************************
	This function will return the location of where the entity would get to
	by continuing with the same direction.
	Output:
	-Point - the new location.
	***********************************************************************/
	Point getNextLocation() const;

	/**************************[setCurLocation]**************************
	This function updates the previous location and sets the new one.
	Input:
	-const Point& new_location - new location to set.
	********************************************************************/
	void setCurLocation(const Point& new_location)
	{
		_prev_location = _cur_location;
		_cur_location = new_location;
	}

	/**************************[display]**************************
	This function prints entity's sign.
	*************************************************************/
	void display() const;

	/**************************[move]***************************
	This function is the main movement function of all entities.
	***********************************************************/
	virtual void move(Board& board, GameDetails& game_details) = 0;

	virtual ~Entity() {}
};

#endif
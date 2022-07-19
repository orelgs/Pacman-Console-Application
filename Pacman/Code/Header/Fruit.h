#ifndef FRUIT_H
#define FRUIT_H

#include "Entity.h"

class Fruit : public Entity
{
private:
	int _value = 0, _time_dead, _time_alive, random_num;
	bool _alive;

	/**************************[generateRandomValue]**************************
	This function will generate a value for the fruit, and set the sign too.
	*************************************************************************/
	void generateRandomValue()
	{
		_value = 5 + rand() % 4;
		setSign(_value + '0');
	}

	/**************************[movement]**************************
	This function is the fruit's actual movement function.
	Input:
	-const Board& board - the game board.
	**************************************************************/
	void movement(const Board& board);

public:
	Fruit();

	/**************************[init]**************************
	This function will initialize a fruit to be alive.
	Input:
	-const Board& board - the game board.
	**********************************************************/
	void init(const Board& board);

	/**************************[kill]**************************
	This function will kill a fruit.
	Input:
	-const Board& board - the game board.
	-const GameMode& mode - the game mode.
	**********************************************************/
	void kill(const Board& board, const GameMode& mode);

	const bool& isAlive() const
	{
		return _alive;
	}

	const int& getValue() const
	{
		return _value;
	}

	/**************************[move]**************************
	Movement function for the fruit.
	**********************************************************/
	void move(Board& board, GameDetails& game_details) override;

	~Fruit() override {}
};

#endif
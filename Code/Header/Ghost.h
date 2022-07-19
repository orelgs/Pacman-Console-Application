#ifndef GHOST_H
#define GHOST_H

#include "Entity.h"
#include <algorithm>

class Ghost : public Entity
{
private:
	Difficulty _difficulty;
	vector<Direction> available_directions;
	int random_num;

	/*************************[moveNoviceGhost]**************************
	This function is the main move function of the Novice ghost.
	Output:
	-const Board& board - the game board.
	********************************************************************/
	void moveNoviceGhost(const Board& board);

	/*************************[moveGoodGhost]**************************
	This function is the main move function of the Good ghost.
	Output:
	-const Board& board - the game board.
	******************************************************************/
	void moveGoodGhost(const Board& board);

	/*************************[moveBestGhost]**************************
	This function is the main move function of the Best ghost.
	Output:
	-const Board& board - the game board.
	******************************************************************/
	void moveBestGhost(const Board& board);

	/*************************[checkAvailableDirections]**************************
	This function will check for all available directions around the current
	ghost's location and update the directions vector.
	Input:
	-const Board& board - the game board.
	*****************************************************************************/
	void checkAvailableDirections(const Board& board);

	/*************************[isValidLocation]**************************
	This function will check the received location to see if the ghost 
	can travel to it.
	Input:
	-const Board& board - the game board.
	-const Point& location - the location to check.
	Output:
	-true - if there's no wall / tunnel / another ghost in the location.
	-false - else.
	********************************************************************/
	bool isValidLocation(const Board& board, const Point& location) const;

public:
	Ghost(const Point& start_location, const Difficulty& difficulty);

	/**************************[move]**************************
	Movement function for the ghosts.
	**********************************************************/
	void move(Board& board, GameDetails& game_details) override;

	~Ghost() override {} 
};

#endif
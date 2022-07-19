#ifndef PACMAN_H
#define PACMAN_H

#include "Entity.h"

class Pacman: public Entity
{
private:
	int _lives, _points, _breadcrumbs_eaten = 0;

public:
	Pacman(const Point& start_location, const int& pacman_start_score, const int& pacman_start_lives);

	void loseALife()
	{
		_lives--;
	}

	bool isDead() const
	{
		return _lives == 0;
	}

	const int& getPoints() const
	{
		return _points;
	}

	const int& getLives() const
	{
		return _lives;
	}

	const int& getBreadcrumbsEaten() const
	{
		return _breadcrumbs_eaten; 
	}

	void eatBreadcrumb()
	{
		_points++;
		_breadcrumbs_eaten++;
	}

	void eatFruit(const int& value)
	{
		_points += value;
	}

	/**************************[move]**************************
	Movement function for pacman.
	**********************************************************/
	void move(Board& board, GameDetails& game_details) override;

	~Pacman() override {}
};

#endif
#ifndef GAMEDETAILS_H
#define GAMEDETAILS_H

#include "Utility.h"

enum class GameStateCode
{
	GAME_NOT_STARTED_CODE = 500,
	GAME_ONGOING_CODE = 365,
	GAME_WON_CODE = 1000,
	GAME_LOST_CODE = 0,
	SILENT_FAILURE = 666
};

enum class DefaultValues
{
	PACMAN_START_POINTS,
	MAX_LIVES = 3
};

enum class GameMode
{
	NORMAL,
	SAVE,
	LOAD,
	SILENT
};

enum class Difficulty
{
	NOVICE,
	GOOD,
	BEST
};

class GameDetails
{
private:
	bool colours = false;
	int _pacman_lives_left, _pacman_accumulated_points;
	Difficulty _difficulty = Difficulty::NOVICE;
	GameStateCode _game_state;
	GameMode _game_mode;
	fstream* _steps_file = nullptr, * _result_file = nullptr;

public:
	GameDetails() { reset(); }

	GameDetails(const GameDetails&) = delete;

	GameDetails& operator=(const GameDetails&) = delete;

	void reset();

	const int& getPacmanLivesLeft() const
	{
		return _pacman_lives_left;
	}

	const int& getPacmanAccumulatedPoints() const
	{
		return _pacman_accumulated_points;
	}

	const GameStateCode& getGameState() const
	{
		return _game_state;
	}

	const Difficulty& getDifficulty() const
	{
		return _difficulty;
	}

	void setDifficulty(const Difficulty& difficulty)
	{
		_difficulty = difficulty;
	}

	void setPacmanLivesLeft(const int& lives)
	{
		_pacman_lives_left = lives;
	}

	void setPacmanAccumulatedPoints(const int& points)
	{
		_pacman_accumulated_points = points;
	}

	void setGameState(const GameStateCode& state)
	{
		_game_state = state;
	}

	void toggleColours()
	{
		colours = !colours;
	}

	const bool& isColours() const { return colours; }

	const GameMode& getGameMode() const
	{
		return _game_mode;
	}

	void setGameMode(GameMode mode) 
	{
		_game_mode = mode;
	}

	void setStepsFile(string screen_file_name);

	void setResultFile(string screen_file_name);

	fstream* getStepsFile() const
	{
		return _steps_file;
	}

	fstream* getResultFile() const
	{
		return _result_file;
	}

	~GameDetails();
};

#endif
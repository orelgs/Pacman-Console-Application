#ifndef GAME_H
#define GAME_H

#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include "GameDetails.h"

enum class Seconds
{
	ONE_SECOND = 1000
};

class Game
{
private:
	GameDetails& _game_details;
	Board& _board;
	vector<Entity*> entities;

	/*************************[isGameWon]**************************
	This function checks if the game is won, by checking if there
	are breadcrumbs left on board.
	Output:
	true if game there are none left, false otherwise.
	**************************************************************/
	bool isGameWon() const;

	/***************************[isGameLost]****************************
	This function checks if the game is lost, by checking if pacman died.
	Output:
	true if pacman is dead, false otherwise.
	*******************************************************************/
	bool isGameLost() const;

	/*************************[isDirectionKey]**************************
	This function checks if the player pressed a direction key.
	Input:
	int key - the pressed key value, by reference.
	Output:
	true if one of the 5 direction keys (including "STAY") is pressed,
	false if any other key.
	*******************************************************************/
	bool isDirectionKey(const int& key) const;

	/*****************[waitThreeSeconds]******************
	This function waits 3 seconds before starting a game.
	*****************************************************/
	void waitThreeSeconds() const;

	/**********************************[pausedGame]***********************************
	This function pauses the game when ESC key is pressed, until ESC is pressed again.
	*********************************************************************************/
	void pausedGame() const;

	/************************[displayEntity]*************************
	This function displays the current and previous entity locations.
	Input:
	Entity* entity - pointer to entity to display.
	****************************************************************/
	void displayEntity(Entity* entity) const;

	/******************[displayScoreboard]*********************
	This function displays the scoreboard.
	**********************************************************/
	void displayScoreboard() const;

	/******************[convertLivesToString]*********************
	This function converts pacmans lives amount into a string.
	Ouput:
	string of "@"s.
	*************************************************************/
	string convertLivesToString() const;

	/*************************************[getKey]*************************************
	This function gets keyCodes for special keys such as w, a, s, d, escape and others
	It returns the key code such as 27 for Escape...
	Output:
	int KeyStroke - the key code for the key pressed
	**********************************************************************************/
	int getKey() const;

	/*************************************[displayAllEntities]*************************************
	This function will display all entities in the game.
	**********************************************************************************************/
	void displayAllEntities() const;

	/*************************************[resetBoard]*************************************
	This function will reset the entities in the board to their start locations.
	**************************************************************************************/
	void resetBoard();

	/*************************************[checkCollision]*************************************
	This function will check for entities collisions, and deal with it.
	******************************************************************************************/
	void checkCollision();

	/*************************************[pacmanMetGhosts]*************************************
	This function will deal with the collision between pacman and ghosts.
	*******************************************************************************************/
	void pacmanMetGhosts();

	/*************************************[updateBoard]*************************************
	This function will update the entities vector in the board.
	***************************************************************************************/
	void updateBoard();

	/******************************[updateGameDetails]******************************
	This function will update the game details after every move.
	*******************************************************************************/
	void updateGameDetails();

public:
	enum EntityLocationInVector
	{
		PACMAN,
		FRUIT,
		GHOST
	};

	enum GameSpeed
	{
		NORMAL_SPEED = 200,
		LOAD_SPEED = 100,
		SILENT_SPEED = 0
	};

	Game(Board& board, GameDetails& game_state);

	Game(const Game& b) = delete;

	Game& operator=(const Game& b) = delete;

	/********************[play]********************
	This function starts the game.
	**********************************************/
	void play();

	~Game();
};

#endif
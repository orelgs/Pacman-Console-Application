#ifndef UI_H
#define UI_H

#include "Game.h"
#include <iostream>
#include <fstream>

enum class UserOptions
{
	NO_SELECTION,
	PLAY,
	BOARD_FILE_SELECTION = 5,
	DIFFICULTY,
	COLOUR,
	INSTRUCTIONS,
	EXIT
};

class UI
{
private:
	GameDetails game_details;
	vector<string> board_files;
	UserOptions selection;
	bool specific_board = false;
	int board_id = 0;

	/*****************************[isSelectionValid]*******************************
	This function will check if the selection is valid or not.
	Input:
	-const int user_selection - the user selection.
	Output:
	-True - if selection is valid
	-False - else
	******************************************************************************/
	bool isSelectionValid(const int& user_selection) const;

	/*****************************[setUserSelection]*******************************
	This function sets the user selection.
	Input:
	-const int m_selection - the user selection.
	******************************************************************************/
	void setUserSelection(const UserOptions& m_selection);

	/*****************************[resetSelection]*******************************
	This function resets the user selection.
	****************************************************************************/
	void resetSelection();

	/*****************************[getSelectionFromUser]*******************************
	This function gets the selection from the user and updates it.
	**********************************************************************************/
	void getSelectionFromUser();

	/********************************[displayMenu]**********************************
	This function prints the game menu.
	Input:
	-bool big_board - true if the currently selected board is big false otherwise
	*******************************************************************************/
	void displayMenu() const;

	/*****************************[displayInstructions]*******************************
	This function prints the game instructions.
	*********************************************************************************/
	void displayInstructions() const;

	/*****************************[displayInstructions]*******************************
	This function prints the goodbye message.
	*********************************************************************************/
	void displayGoodbyeMessage() const;

	/*****************************[printGameLost]*******************************
	This function prints game over when the user lost.
	***************************************************************************/
	void printGameLost() const;

	/*****************************[printGameWon]*******************************
	This function congratulations the user when they won the game.
	**************************************************************************/
	void printGameWon() const;

	/**************************[printBoardSelection]***************************
	This function allows to choose a specific board.
	**************************************************************************/
	void printBoardSelection();

	/**********************[waitForReaction]***********************
	This function waits till the user presses a key.
	**************************************************************/
	void waitForReaction() const;

	/****************[convertTextFileToStringVector]*****************
	This function converts the text file recieved into a string
	vector that contains the board.
	Input:
	- const string& file_name - name of file to convert.
	****************************************************************/
	vector<string> convertTextFileToStringVector(const string& file_name) const;

	/********************[handleScoreboardLocation]*********************
	This function makes changes to the original board according to the
	location of the scoreboard.
	Input:
	- vector<string>& strings - the current board.
	*******************************************************************/
	void handleScoreboardLocation(vector<string>& strings) const;

	/***************[getAllBoardFilesFromDirectory]****************
	This function gets board files from folder.
	**************************************************************/
	vector<string> getAllBoardFilesFromDirectory();

	void determineGameMode(int argc, char* argv[]);

public:
	UI() 
	{
		board_files = getAllBoardFilesFromDirectory();
		selection = UserOptions::NO_SELECTION;
	}

	/*****************************[options]*******************************
	This function deals with the user's option selection and can start
	a new game.
	*********************************************************************/
	void options(int argc, char* argv[]);
};

#endif
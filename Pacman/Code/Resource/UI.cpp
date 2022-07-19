#include "../Header/UI.h"

bool UI::isSelectionValid(const int& user_selection) const
{
	bool result = false;

	switch (user_selection)
	{
	case ((int)UserOptions::PLAY):
	case ((int)UserOptions::BOARD_FILE_SELECTION):
	case ((int)UserOptions::DIFFICULTY):
	case ((int)UserOptions::COLOUR):
	case ((int)UserOptions::INSTRUCTIONS):
	case ((int)UserOptions::EXIT):
		result = true;
		break;
	}
	return result;
}

void UI::setUserSelection(const UserOptions& m_selection)
{
	selection = m_selection;
}

void UI::resetSelection()
{
	selection = UserOptions::NO_SELECTION;
}

void UI::getSelectionFromUser()
{
	int user_selection = _getch() - '0';

	while (!isSelectionValid(user_selection))
		user_selection = _getch() - '0';

	setUserSelection((UserOptions)user_selection);
}

void UI::displayMenu() const
{
	system("cls"); 

	if (game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::YELLOW);

	cout << "---------------------------------------- " << endl;
	cout << "|          Welcome to Pacman!          | " << endl;
	cout << "---------------------------------------- " << endl;

	if (game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::WHITE);

	cout << "Please select an option:" << endl;
	cout << "1. Start a new game." << endl;
	cout << "5. Specific board selection." << endl;
	cout << "   Currently selected: ";
	if (specific_board)
		cout << board_files[board_id];
	else
		cout << "All boards.";
	cout << endl;
	cout << "6. Toggle game difficulty." << endl;
	cout << "   Currently selected difficulty: ";
	switch (game_details.getDifficulty())
	{
	case Difficulty::NOVICE:
		cout << "NOVICE." << endl;
		break;
	case Difficulty::GOOD:
		cout << "GOOD." << endl;
		break;
	case Difficulty::BEST:
		cout << "BEST." << endl;
		break;
	}
	cout << "7. Toggle colours ON / OFF." << endl;
	cout << "8. Instructions and Keys." << endl;
	cout << "9. Exit." << endl;
}

void UI::displayInstructions() const
{
	if (game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::YELLOW);

	cout << "---------------------------------------- " << endl;
	cout << "|             Instructions             | " << endl;
	cout << "---------------------------------------- " << endl;

	if (game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::WHITE);

	cout << "Welcome to Pacman!" << endl;
	cout << "In this game you play as the pacman. Collect all the breadcrumbs to win!" << endl;
	cout << "But beware of the ghosts, if they touch you, you lose a life!" << endl;
	cout << "Lose all 3 lives and it's game over." << endl << endl;

	cout << "Keys:" << endl;
	cout << "------------------------------------- " << endl;
	cout << "Left - A" << endl;
	cout << "------------------------------------- " << endl;
	cout << "Right - D" << endl;
	cout << "------------------------------------- " << endl;
	cout << "Up - W" << endl;
	cout << "------------------------------------- " << endl;
	cout << "Down - X" << endl;
	cout << "------------------------------------- " << endl;
	cout << "Stay - S" << endl;
	cout << "------------------------------------- " << endl;
	cout << "Pause - ESC" << endl;
	cout << "------------------------------------- " << endl << endl;
	cout << "Press ESC to return to the main menu." << endl;
	while (!_kbhit() || _getch() != 27)
		Sleep(100);
}

void UI::displayGoodbyeMessage() const
{
	if (game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::RED);

	cout << "---------------------------------------- " << endl;
	cout << "|              Goodbye :)              | " << endl;
	cout << "---------------------------------------- " << endl;

	if (game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::WHITE);
}

vector<string> UI::convertTextFileToStringVector(const string& file_name) const
{
	ifstream file(file_name);
	string cur_line = "";
	char cur_char;
	vector<string> strings;

	cur_char = file.get();

	while (cur_char != '\n' && !file.eof())
	{
		if (cur_char == ' ')
			cur_char = '.';
		else if (cur_char == '%')
			cur_char = ' ';
		cur_line.push_back(cur_char);
		cur_char = file.get();
	}

	strings.push_back(cur_line);

	while (!file.eof())
	{
		cur_line = "";
		cur_char = file.get();
		while (cur_char != '\n' && !file.eof())
		{
			if (cur_char == ' ')
				cur_char = '.';
			else if (cur_char == '%')
				cur_char = ' ';
			if (cur_line.size() <= strings[0].size())
				cur_line.push_back(cur_char);
			cur_char = file.get();
		}
		while (cur_line.size() < strings[0].size())
			cur_line.push_back(' ');
		strings.push_back(cur_line);
	}

	file.close();

	handleScoreboardLocation(strings);
	return strings;
}

void UI::handleScoreboardLocation(vector<string>& strings) const
{
	Point scoreboard_location;

	for (int i = 0; i < strings.size(); i++)
	{
		for (int j = 0; j < strings[0].size(); j++)
			if (strings[i][j] == '&')
				scoreboard_location = Point(j, i);
	}

	int original_height, original_width;

	original_height = strings.size();
	original_width = strings[0].size();

	if (original_height - scoreboard_location.getY() < 3)
	{
		for (int i = 0; i < 3 - (original_height - scoreboard_location.getY()); i++)
		{
			string line_to_add = "";
			for (int j = 0; j < original_width; j++)
			{
				if (j >= scoreboard_location.getX() && j <= scoreboard_location.getX() + 19)
					line_to_add.push_back(' ');
				else
					line_to_add.push_back('.');
			}
			strings.push_back(line_to_add);
		}
			
	}
	if (original_width - scoreboard_location.getX() < 20)
	{
		for (int i = 0; i < strings.size(); i++)
		{
			string line_to_add = "";
			for (int j = 0; j < 20 - (original_width - scoreboard_location.getX()); j++)
			{
				if (i >= scoreboard_location.getY() && i <= scoreboard_location.getY() + 2)
					line_to_add.push_back(' ');
				else
					line_to_add.push_back('.');
			}
			strings[i].append(line_to_add);
		}
	}

	for (int i = scoreboard_location.getY(); i < scoreboard_location.getY() + 3; i++)
	{
		for (int j = scoreboard_location.getX(); j < scoreboard_location.getX() + 20; j++)
		{
			if (!scoreboard_location.isEqual(Point(j, i)))
				strings[i][j] = ' ';
		}
	}
}

vector<string> UI::getAllBoardFilesFromDirectory()
{
	vector<string> files;

	for (const auto& entry : fs::directory_iterator("."))
	{
		size_t index_of_pacman, index_of_screen;
		string file_name = entry.path().string();
		index_of_pacman = file_name.find("pacman_");
		index_of_screen = file_name.find(".screen");
		if (index_of_pacman == 2 && index_of_screen != string::npos && file_name[index_of_screen + 7] == '\0')
			files.push_back(entry.path().string());
	}

	return files;
}

void UI::printGameLost() const
{
	if (game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::RED);

	cout << "-----------------------------------------" << endl;
	cout << "|          SORRY! YOU'VE LOST!          |" << endl;
	cout << "-----------------------------------------" << endl << endl;
}

void UI::printGameWon() const
{
	if (game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::LIGHTGREEN);

	cout << "-----------------------------------------" << endl;
	cout << "|       CONGRATULATIONS! YOU WIN!       |" << endl;
	cout << "-----------------------------------------" << endl << endl;
}

void UI::printBoardSelection()
{
	if (game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::YELLOW);

	cout << "----------------------------------------" << endl;
	cout << "|            BOARD SELECTION           |" << endl;
	cout << "----------------------------------------" << endl;

	if (game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::WHITE);

	cout << "Please choose one of the following boards:" << endl;
	cout << "0. No specific board selection." << endl;

	for (int i = 1; i <= board_files.size(); i++)
		cout << i << ". " << board_files[i - 1] << endl;

	int user_selection = _getch() - '0';

	while (user_selection < 0 || user_selection > board_files.size())
		user_selection = _getch() - '0';

	if (user_selection != 0)
	{
		specific_board = true;
		board_id = user_selection - 1;
	}
}

void UI::waitForReaction() const
{
	if (game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::WHITE);

	cout << "Press any key to return to the main menu." << endl;

	Sleep((int)Seconds::ONE_SECOND);

	while (!_kbhit())
		Sleep((int)Seconds::ONE_SECOND);
	_getch();
}

void UI::determineGameMode(int argc, char* argv[])
{
	if (argc < 2)
		game_details.setGameMode(GameMode::NORMAL);
	else if (argc == 2)
	{
		if (strcmp(argv[1], "-load") == 0)
			game_details.setGameMode(GameMode::LOAD);
		else if (strcmp(argv[1], "-save") == 0)
			game_details.setGameMode(GameMode::SAVE);
		else
			throw "Wrong command.";
			
	}
	else if (argc == 3)
	{
		if (strcmp(argv[1], "-load") == 0 && strcmp(argv[2], "-silent") == 0)
			game_details.setGameMode(GameMode::SILENT);
		else if (strcmp(argv[1], "-save") == 0 && strcmp(argv[2], "-silent") == 0)
			game_details.setGameMode(GameMode::SAVE);
		else
			throw "Wrong command.";
	}
	else
		throw "Wrong command.";
}

void UI::options(int argc, char* argv[])
{	
	system("cls");
	srand(time(NULL));

	try
	{
		determineGameMode(argc, argv);
	}
	catch(const char*)
	{
		selection = UserOptions::EXIT;
		cout << "Wrong command line usage, please use the following format:" << endl;
		cout << "Pacman.exe -save / -load / -load -silent" << endl;
	}

	vector<vector<string>> boards;

	for (auto it : board_files)
		boards.push_back(convertTextFileToStringVector(it));

	if (game_details.getGameMode() == GameMode::LOAD || game_details.getGameMode() == GameMode::SILENT)
	{
		game_details.setGameState(GameStateCode::GAME_ONGOING_CODE);
		selection = UserOptions::PLAY;
	}

	while (selection != UserOptions::EXIT) {
		if (game_details.getGameState() == GameStateCode::GAME_NOT_STARTED_CODE)
		{
			displayMenu();
			getSelectionFromUser();
			system("cls");
		}

		if (selection == UserOptions::PLAY)
		{
			if (board_files.size() != 0)
			{
				Board board(boards[board_id]);

				game_details.setStepsFile(board_files[board_id]);
				game_details.setResultFile(board_files[board_id]);

				if (specific_board)
					board_id = boards.size() - 1;
				
				Game(board, game_details).play();
			}
			else
			{
				cout << "No proper board files detected in the directory!" << endl << endl;
				waitForReaction();
			}
		}
		else if (selection == UserOptions::BOARD_FILE_SELECTION)
		{
			if (board_files.size() != 0)
			{
				system("cls");
				printBoardSelection();
			}
			else
			{
				cout << "No proper board files detected in the directory!" << endl << endl;
				waitForReaction();
			}
		}
		else if (selection == UserOptions::DIFFICULTY)
			game_details.setDifficulty((Difficulty)(((int)game_details.getDifficulty() + 1) % 3));
		else if (selection == UserOptions::COLOUR)
		{
			game_details.toggleColours();
			if (!game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::LIGHTGREY);
		}
		else if (selection == UserOptions::INSTRUCTIONS)
			displayInstructions();
		else if (selection == UserOptions::EXIT)
			displayGoodbyeMessage();

		if (game_details.getGameState() == GameStateCode::GAME_WON_CODE)
		{
			board_id++;
			if (board_id == boards.size())
			{
				if (game_details.getGameMode() != GameMode::SILENT)
				{
					printGameWon();
					if (game_details.getGameMode() == GameMode::LOAD)
					{
						Sleep(1000);
						selection = UserOptions::EXIT;
					}
					else
						waitForReaction();
				}
				else
				{
					cout << "Test Passed." << endl;
					selection = UserOptions::EXIT;
				}
				board_id = 0;
				specific_board = false;
				game_details.reset();
			}
			else
				game_details.setGameState(GameStateCode::GAME_ONGOING_CODE);
		}
		else if (game_details.getGameState() == GameStateCode::GAME_LOST_CODE)
		{
			if (game_details.getGameMode() != GameMode::SILENT)
			{
				printGameLost();
				if (game_details.getGameMode() == GameMode::LOAD)
				{
					Sleep(1000);
					selection = UserOptions::EXIT;
				}
				else
					waitForReaction();
			}
			else
			{
				cout << "Test Passed." << endl;
				selection = UserOptions::EXIT;
			}
			board_id = 0;
			specific_board = false;
			game_details.reset();
		}
		else if (game_details.getGameState() == GameStateCode::SILENT_FAILURE)
		{
			cout << "Test Failed." << endl;
			selection = UserOptions::EXIT;
		}
	}
}
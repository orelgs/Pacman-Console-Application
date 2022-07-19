#include "../Header/Game.h"

Game::Game(Board& board, GameDetails& game_details) : _board(board), _game_details(game_details)
{
	_board.setColours(_game_details.isColours());
	_game_details.setGameState(GameStateCode::GAME_ONGOING_CODE);
	entities.push_back(new Pacman(_board.getPacmanStartLocation(), _game_details.getPacmanAccumulatedPoints(), _game_details.getPacmanLivesLeft()));
	entities.push_back(new Fruit());
	for (int i = 0; i < _board.getGhostStartLocations().size(); i++)
		entities.push_back(new Ghost(_board.getGhostStartLocations()[i], _game_details.getDifficulty()));
}

Game::~Game()
{
	for (auto it = entities.begin(); it != entities.end(); it++)
		delete* it;
}

int Game::getKey() const
{
	char key_stroke = _getch();
	if (key_stroke == 0 || key_stroke == -32)
		key_stroke = _getch();

	if (key_stroke == 'w' || key_stroke == 'x' || key_stroke == 'a' || key_stroke == 'd' || key_stroke == 's')
		key_stroke = toupper(key_stroke);

	return key_stroke;
}

void Game::pacmanMetGhosts()
{
	((Pacman*)entities[PACMAN])->loseALife();
	resetBoard();

	if (_game_details.getGameMode() != GameMode::SILENT)
		displayScoreboard();
	((Pacman*)entities[PACMAN])->setDirection(Direction::STAY);
	for (auto it = entities.begin() + 2; it != entities.end(); it++)
		(*it)->resetMoveCount();
	((Fruit*)entities[FRUIT])->kill(_board, _game_details.getGameMode());
	if (!((Pacman*)entities[PACMAN])->isDead() && _game_details.getGameMode() != GameMode::SILENT && _game_details.getGameMode() != GameMode::LOAD)
		waitThreeSeconds();
	throw "Pacman died.";
}

void Game::checkCollision()
{
	for (auto it1 = entities.begin(); it1 != entities.end() - 1; it1++)
	{
		for (auto it2 = it1 + 1; it2 != entities.end(); it2++)
		{
			if ((*it1)->getCurLocation().isEqual((*it2)->getCurLocation()))
			{
				if (typeid(**it1) == typeid(Pacman) && typeid(**it2) == typeid(Ghost))
					pacmanMetGhosts();
				if (((Fruit*)entities[FRUIT])->isAlive())
				{
					if (typeid(**it1) == typeid(Pacman) && typeid(**it2) == typeid(Fruit))
					{
						((Pacman*)*it1)->eatFruit(((Fruit*)*it2)->getValue());
						((Fruit*)*it2)->kill(_board, _game_details.getGameMode());
					}
					if (typeid(**it1) == typeid(Fruit) && typeid(**it2) == typeid(Ghost))
						((Fruit*)*it1)->kill(_board, _game_details.getGameMode());
				}
			}
		}
	}
}

void Game::resetBoard()
{
	updateBoard();
	displayAllEntities();

	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		if (typeid(**it) != typeid(Fruit))
		{
			(*it)->setCurLocation((*it)->getStartLocation());
		}
	}
	updateBoard();
	displayAllEntities();
}

void Game::displayAllEntities() const
{
	if (_game_details.getGameMode() != GameMode::SILENT)
	{
		for (auto it = entities.begin(); it != entities.end(); it++)
			displayEntity(*it);
	}
}

bool Game::isGameWon() const
{
	return _board.getBreadcrumbsOnBoard() == ((Pacman*)entities[PACMAN])->getBreadcrumbsEaten();
}

bool Game::isGameLost() const
{
	return ((Pacman*)entities[PACMAN])->isDead();
}

void Game::waitThreeSeconds() const
{
	for (int i = 3; i >= 1; i--) {
		Utility().gotoxy(0, -1);
		cout << "Game starting in... " << i;
		Sleep((int)Seconds::ONE_SECOND);
	}
	Utility().gotoxy(0, -1);
	cout << "                                   ";
}

void Game::pausedGame() const 
{
	Utility().gotoxy(0, -1);
	cout << "Game paused, press ESC to continue.";
	while (!_kbhit() || _getch() != 27)
		Sleep(100);
	Utility().gotoxy(0, -1);
	cout << "                                   ";
}

bool Game::isDirectionKey(const int& key) const
{
	Direction _key = (Direction)key;
	return _key == Direction::UP || _key == Direction::DOWN || _key == Direction::LEFT || _key == Direction::RIGHT || _key == Direction::STAY;
}

void Game::displayEntity(Entity* entity) const
{
	if (typeid(*entity) != typeid(Fruit) || ((Fruit*)entity)->isAlive())
	{
		if (!entity->getCurLocation().isEqual(entity->getPrevLocation()) && _board.isLocationEmpty(entity->getPrevLocation()))
			_board.displaySingleCoordinate(entity->getPrevLocation());

		if (typeid(*entity) == typeid(Pacman))
		{
			if (_game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::YELLOW);
		}
		else if (typeid(*entity) == typeid(Ghost))
		{
			if (_game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::RED);
		}
		else if (typeid(*entity) == typeid(Fruit))
		{
			if (_game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::LIGHTGREEN);
		}
		entity->display();
	}
}

string Game::convertLivesToString() const
{
	string lives_string = "";
	int pacman_lives = ((Pacman*)entities[PACMAN])->getLives();
	for (int i = 0; i < pacman_lives; i++)
		lives_string.append("@");

	return lives_string;
}

void Game::displayScoreboard() const
{
	if (_game_details.isColours()) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Colours::WHITE);
	Utility().gotoxy(_board.getScoreboardLocation().getX(), _board.getScoreboardLocation().getY());
	cout << "                    ";
	Utility().gotoxy(_board.getScoreboardLocation().getX(), _board.getScoreboardLocation().getY());
	cout << "  Lives: " << convertLivesToString();
	Utility().gotoxy(_board.getScoreboardLocation().getX(), _board.getScoreboardLocation().getY() + 1);
	cout << "                    ";
	Utility().gotoxy(_board.getScoreboardLocation().getX(), _board.getScoreboardLocation().getY() + 2);
	cout << "                    ";
	Utility().gotoxy(_board.getScoreboardLocation().getX(), _board.getScoreboardLocation().getY() + 2);
	cout << "  Points: " << ((Pacman*)entities[PACMAN])->getPoints();
}

void Game::updateBoard()
{
	vector<Point> locations;
	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		if (typeid(**it) != typeid(Fruit))
			locations.push_back((*it)->getCurLocation());
	}
	_board.updateEntitiesLocations(locations);
}

void Game::updateGameDetails()
{
	_game_details.setPacmanAccumulatedPoints(((Pacman*)entities[PACMAN])->getPoints());
	_game_details.setPacmanLivesLeft(((Pacman*)entities[PACMAN])->getLives());

	if (isGameWon()) {
		_game_details.setGameState(GameStateCode::GAME_WON_CODE);

		if (_game_details.getGameMode() != GameMode::SILENT)
			Sleep((int)Seconds::ONE_SECOND);
	}
	if (isGameLost()) {
		_game_details.setGameState(GameStateCode::GAME_LOST_CODE);
		
		if (_game_details.getGameMode() != GameMode::SILENT)
			Sleep((int)Seconds::ONE_SECOND);
	}
}

void Game::play()
{
	int key_pressed, pacman_moves_counter, index_in_entities_array, game_speed;
	char entity_to_move;

	switch (_game_details.getGameMode())
	{
	case GameMode::SAVE:
	case GameMode::NORMAL:
		game_speed = NORMAL_SPEED;
		break;
	case GameMode::LOAD:
		game_speed = LOAD_SPEED;
		break;
	case GameMode::SILENT:
		game_speed = SILENT_SPEED;
		break;
	}

	if (_game_details.getGameMode() != GameMode::SILENT)
	{
		_board.displayWallsAndBreadcrumbs();
		displayAllEntities();
		displayScoreboard();
	}
	
	updateBoard();

	if (_game_details.getGameMode() != GameMode::SILENT && _game_details.getGameMode() != GameMode::LOAD)
		waitThreeSeconds();

	if (_game_details.getGameMode() == GameMode::LOAD || _game_details.getGameMode() == GameMode::SILENT)
	{
		_game_details.getStepsFile()->get(entity_to_move);
		_game_details.getStepsFile()->get();
	}
	
	while (_game_details.getGameState() == GameStateCode::GAME_ONGOING_CODE) {

		Sleep(game_speed);

		if (_kbhit() && (_game_details.getGameMode() == GameMode::SAVE || _game_details.getGameMode() == GameMode::NORMAL)) {
			key_pressed = getKey();

			if (isDirectionKey(key_pressed))
				((Pacman*)entities[PACMAN])->setDirection((Direction) key_pressed);
			else if (key_pressed == (int) Direction::ESC) {
				pausedGame();
				key_pressed = 0;
			}
		}

		pacman_moves_counter = ((Pacman*)entities[PACMAN])->getMovesCount();
		
		index_in_entities_array = 0;

		for (auto it = entities.begin(); it != entities.end(); it++, index_in_entities_array++)
		{
			if (typeid(**it) == typeid(Pacman) || (typeid(**it) == typeid(Ghost) && pacman_moves_counter % 2 == 0) || (typeid(**it) == typeid(Fruit) && pacman_moves_counter % 3 == 0))
			{
				if (_game_details.getGameMode() == GameMode::SAVE || _game_details.getGameMode() == GameMode::NORMAL || index_in_entities_array == entity_to_move - '0')
				{
					(*it)->move(_board, _game_details);

					pacman_moves_counter = ((Pacman*)entities[PACMAN])->getMovesCount();

					if (_game_details.getGameMode() == GameMode::LOAD || _game_details.getGameMode() == GameMode::SILENT)
					{
						_game_details.getStepsFile()->get(entity_to_move);
						_game_details.getStepsFile()->get();
					}
				}
				
				if (_game_details.getGameMode() == GameMode::SAVE)
				{
					if (index_in_entities_array != 1 || (((Fruit*)*it)->isAlive() && (*it)->getDirection() != Direction::STAY))
						*(_game_details.getStepsFile()) << index_in_entities_array << " " << (char)(*it)->getDirection() << endl;
				}
			}
			try
			{
				updateBoard();
				checkCollision();

				if (_game_details.getGameMode() != GameMode::SILENT)
					displayEntity(*it);
			}
			catch (const char*)
			{
				if (_game_details.getGameMode() == GameMode::SAVE)
					*(_game_details.getResultFile()) << "PacmanDeath " << pacman_moves_counter << endl;
				else if (_game_details.getGameMode() == GameMode::SILENT)
				{
					char cur_line[30];
					_game_details.getResultFile()->getline(cur_line, 29, '\n');
					std::stringstream sstream(cur_line);
					string action;

					sstream >> action;

					if (action == "PacmanDeath")
					{
						int time_stamp;
						sstream >> time_stamp;
						if (time_stamp != pacman_moves_counter)
							_game_details.setGameState(GameStateCode::SILENT_FAILURE);
					}
				}
				break;
			}
		}

		if (_game_details.getGameMode() != GameMode::SILENT)
			displayScoreboard();

		updateGameDetails();

		if (_game_details.getGameState() == GameStateCode::GAME_WON_CODE)
		{
			if (_game_details.getGameMode() == GameMode::SAVE)
				*(_game_details.getResultFile()) << "FinishedScreen " << pacman_moves_counter << endl;
			else if (_game_details.getGameMode() == GameMode::SILENT)
			{
				char cur_line[30];
				_game_details.getResultFile()->getline(cur_line, 29, '\n');
				std::stringstream sstream(cur_line);
				string action;

				sstream >> action;

				if (action == "FinishedScreen")
				{
					int time_stamp;
					sstream >> time_stamp;
					if (time_stamp != pacman_moves_counter)
						_game_details.setGameState(GameStateCode::SILENT_FAILURE);
				}
			}
		}

		Utility().gotoxy(75, 21);
	}

	system("cls");
}
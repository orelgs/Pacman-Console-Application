#include "../Header/GameDetails.h"

void GameDetails::reset()
{
	_pacman_lives_left = (int)DefaultValues::MAX_LIVES;
	_pacman_accumulated_points = (int)DefaultValues::PACMAN_START_POINTS;
	_game_state = GameStateCode::GAME_NOT_STARTED_CODE;

	if (_steps_file != nullptr)
	{
		_steps_file->close();
		delete _steps_file;
		_steps_file = nullptr;
	}

	if (_result_file != nullptr)
	{
		_result_file->close();
		delete _result_file;
		_result_file = nullptr;
	}
}

void GameDetails::setStepsFile(string screen_file_name)
{
	screen_file_name.resize(screen_file_name.size() - 6);
	screen_file_name.append("steps");

	if (_steps_file != nullptr)
	{
		_steps_file->close();
		delete _steps_file;
		_steps_file = nullptr;
	}

	if (_game_mode == GameMode::SAVE)
	{
		_steps_file = new fstream(screen_file_name, std::ios_base::out, std::ios_base::trunc);
		if (colours)
			*_steps_file << "Colours +" << endl;
		else
			*_steps_file << "Colours -" << endl;
	}
	else if (_game_mode == GameMode::NORMAL)
		_steps_file = nullptr;
	else
	{
		_steps_file = new fstream(screen_file_name, std::ios_base::in);

		if (_game_mode == GameMode::LOAD || _game_mode == GameMode::SILENT)
		{
			char cur_line[30];
			(*_steps_file).getline(cur_line, 29, '\n');
			std::stringstream sstream(cur_line);
			string colour;
			sstream >> colour;
			sstream >> colour;
			if (colour == "+")
				colours = true;
			else
				colours = false;
		}
	}
}

void GameDetails::setResultFile(string screen_file_name)
{
	screen_file_name.resize(screen_file_name.size() - 6);
	screen_file_name.append("result");

	if (_result_file != nullptr)
	{
		_result_file->close();
		delete _result_file;
		_result_file = nullptr;
	}

	if (_game_mode == GameMode::SAVE)
		_result_file = new fstream(screen_file_name, std::ios_base::out, std::ios_base::trunc);
	else if (_game_mode == GameMode::NORMAL)
		_steps_file = nullptr;
	else
		_result_file = new fstream(screen_file_name, std::ios_base::in);
}

GameDetails::~GameDetails()
{
	if (_steps_file != nullptr)
	{
		_steps_file->close();
		delete _steps_file;
		_steps_file = nullptr;
	}

	if (_result_file != nullptr)
	{
		_result_file->close();
		delete _result_file;
		_result_file = nullptr;
	}
}
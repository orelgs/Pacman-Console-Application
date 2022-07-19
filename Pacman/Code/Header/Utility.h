#ifndef UTILITY_H
#define UTILITY_H


#include <iostream>
#include <process.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>
namespace fs = std::filesystem;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;

#include "Colours.h"

enum class BoardEdge
{
	BOARD_TOP_LEFT_X = 0,
	BOARD_TOP_LEFT_Y = 1
};

class Utility
{
private:
	int _board_top_left_x, _board_top_left_y;

public:
	Utility(const int& board_top_left_x = (int)BoardEdge::BOARD_TOP_LEFT_X, const int& board_top_left_y = (int)BoardEdge::BOARD_TOP_LEFT_Y);

	void gotoxy(int x, int y) const;
};

#endif
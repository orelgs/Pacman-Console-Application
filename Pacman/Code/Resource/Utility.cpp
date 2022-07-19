#include "../Header/Utility.h"

Utility::Utility(const int& board_top_left_x, const int& board_top_left_y)
{
	_board_top_left_x = board_top_left_x;
	_board_top_left_y = board_top_left_y;
}

void Utility::gotoxy(int x, int y) const
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x + _board_top_left_x;
	dwCursorPosition.Y = y + _board_top_left_y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
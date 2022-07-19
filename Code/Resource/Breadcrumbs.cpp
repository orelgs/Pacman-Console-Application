#include "../Header/Breadcrumbs.h"

Breadcrumbs::Breadcrumbs(const int& board_width, const int& board_height)
{
	_board_width = board_width;
	_board_height = board_height;

	_layout = new bool* [board_width];

	for (int i = 0; i < board_width; i++)
		_layout[i] = new bool[board_height];

	for (int i = 0; i < board_width; i++) {
		for (int j = 0; j < board_height; j++)
			_layout[i][j] = false;
	}
}

Breadcrumbs::~Breadcrumbs()
{
	for (int i = 0; i < _board_width; i++)
		delete[] _layout[i];
	delete[] _layout;
}
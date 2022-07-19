#ifndef BREADCRUMBS_H
#define BREADCRUMBS_H

#include "Point.h"

class Breadcrumbs
{
private:
	int _board_width, _board_height;
	bool** _layout;

public:
	Breadcrumbs(const int& board_width, const int& board_height);

	Breadcrumbs(const Breadcrumbs&) = delete;

	Breadcrumbs& operator=(const Breadcrumbs&) = delete;

	/******************************[isBreadcrumb]*******************************
	This function checks if there is a breadcrumb in given location.
	Input:
	-Point location - location to check
	Output:
	-true if there is a breadcrumb, false otherwise.
	***************************************************************************/
	const bool& isBreadcrumb(const Point& location) const
	{
		return _layout[location.getX()][location.getY()];
	}

	/**************************[setBreadcrumb]**************************
	This function sets a breadcrumb in current location in breadcrumbs
	layout.
	Input:
	-const Point& location - location to update, by reference.
	-const bool& value = true - default value.
	*******************************************************************/
	void setBreadcrumb(const Point& location, const bool& value = true)
	{
		_layout[location.getX()][location.getY()] = value;
	}

	~Breadcrumbs();
};

#endif
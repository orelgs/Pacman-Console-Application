#include "../Header/Point.h"

bool Point::isEqual(Point point_to_compare) const
{
	return _x == point_to_compare.getX() && _y == point_to_compare.getY();
}
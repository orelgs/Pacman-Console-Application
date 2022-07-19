#include "../Header/Entity.h"

void Entity::display() const
{
	Utility().gotoxy(_cur_location.getX(), _cur_location.getY());
	cout << _sign;
}

Point Entity::getNextLocation() const
{
	Point location = getCurLocation();

	switch (getDirection()) {
	case Direction::RIGHT:
		location.setX(location.getX() + 1);
		break;
	case Direction::DOWN:
		location.setY(location.getY() + 1);
		break;
	case Direction::LEFT:
		location.setX(location.getX() - 1);
		break;
	case Direction::UP:
		location.setY(location.getY() - 1);
		break;
	case Direction::STAY:
		break;
	}

	return location;
}
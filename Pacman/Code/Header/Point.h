#ifndef POINT_H
#define POINT_H

class Point
{
private:
	int _x = 0, _y = 0;

public:
	Point() {}

	Point(int x, int y)
	{
		_x = x;
		_y = y;
	}

	const int& getX() const
	{
		return _x;
	}

	const int& getY() const {
		return _y;
	}

	void setX(const int& x)
	{
		_x = x;
	}

	void setY(const int& y)
	{
		_y = y;
	}

	bool operator==(const Point& pt) const
	{
		return _x == pt.getX() && _y == pt.getY();
	}

	/******************[isEqual]*********************
	This function checks if two points are equal.
	Input:
	-Point point_to_compare - point to compare to.
	Ouput:
	-true if they are equal, false otherwise.
	************************************************/
	bool isEqual(Point point_to_compare) const;
};

#endif
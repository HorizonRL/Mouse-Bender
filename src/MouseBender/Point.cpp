#include "Point.h"

Point::Point(int x, int y) 
	: m_x(x) 
	, m_y(y)
{}

Point::Point() 
	: Point(0, 0)
{}

Point Point::from_winapi_point(const POINT& winapi_point)
{
	return Point(winapi_point.x, winapi_point.y);
}

int Point::get_x() const
{
	return m_x;
}

int Point::get_y() const
{
	return m_y;
}

void Point::set_x(const int x)
{
	m_x += x;
}

void Point::set_y(const int y)
{
	m_y += y;
}

std::wstring Point::to_string() const
{
	return std::wstring();
}

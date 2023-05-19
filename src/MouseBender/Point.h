#pragma once
#include <string>
#include <Windows.h>

class Point
{
public:
	Point(int x, int y);
	Point();

public:
	static Point from_winapi_point(const POINT& winapi_point);

public:
	int get_x() const;
	int get_y() const;
	
	void set_x(const int x);
	void set_y(const int y);

	std::wstring to_string() const;

private:
	int m_x;
	int m_y;
};


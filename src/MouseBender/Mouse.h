#pragma once
#include "Point.h"


namespace mouse
{
	void hide();
	void show();
	Point get_pos();
	void set_pos(const Point& point);
	size_t get_width();
	size_t get_height();
};
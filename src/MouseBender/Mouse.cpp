#include "Mouse.h"
#include <Windows.h>


void mouse::hide()
{
}

void mouse::show()
{
}

Point mouse::get_pos()
{
	POINT raw_cursor_pos;
	const BOOL has_succeed = GetCursorPos(&raw_cursor_pos);
	
	if (!has_succeed)
	{
		// TODO: throw smth
	}

	return Point::from_winapi_point(raw_cursor_pos);
}

void mouse::set_pos(const Point& point)
{
	const BOOL has_succeed = SetCursorPos(point.get_x(), point.get_y());

	if (!has_succeed)
	{
		// TODO: throw smth
	}
}

size_t mouse::get_width()
{
	return static_cast<size_t>(GetSystemMetrics(SM_CXCURSOR));
}

size_t mouse::get_height()
{
	return static_cast<size_t>(GetSystemMetrics(SM_CYCURSOR));
}

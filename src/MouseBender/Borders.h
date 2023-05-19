#pragma once
#include "Mouse.h"
#include <vector>
#include <memory>
#include <map>


constexpr size_t NEAR_BORDER_MARGIN_PIXELS = 5;
constexpr size_t AMOUNT_OF_BORDER_LINE_PER_MONITOR = 4;


enum class BorderLocation
{
	RIGHT,
	LEFT,
	TOP,
	BOTTOM,
	NONE
};

enum class BorderType
{
	VERTICAL,
	HORIZONTAL,
	NONE
};

struct BorderLine
{
	BorderLocation side;
	int location;

	BorderType get_border_type()
	{
		switch (side)
		{
		case BorderLocation::RIGHT:
		case BorderLocation::LEFT:
			return BorderType::VERTICAL;

		case BorderLocation::TOP:
		case BorderLocation::BOTTOM:
			return BorderType::HORIZONTAL;

		default:
			return BorderType::NONE;
		}
	}
};

struct MonitorShape
{
	int left;
	int top;
	int right;
	int bottom;
};

class BorderedMonitor 
{
public:
	explicit BorderedMonitor(
		const BorderLine& left_border, const BorderLine& top_border,
		const BorderLine& right_border, const BorderLine& bottom_border);

	explicit BorderedMonitor();

public:
	BorderLine get_left_border() const;
	BorderLine get_top_border() const;
	BorderLine get_right_border() const;
	BorderLine get_bottom_border() const;
	std::vector<BorderLine> get_borders() const;

protected:
	BorderLine m_left_border;
	BorderLine m_top_border;
	BorderLine m_right_border;
	BorderLine m_bottom_border;
};

class PhysicalMonitor : public BorderedMonitor
{

public:
	PhysicalMonitor(
		const MonitorShape& shape, const BorderLine& left_border, const BorderLine& top_border,
		const BorderLine& right_border, const BorderLine& bottom_border);

public:
	bool is_inside() const;

private:
	MonitorShape m_shape;
};


class MonitorsLayout : public BorderedMonitor
{
public:
	MonitorsLayout(const std::vector<PhysicalMonitor>& monitors);

public:
	static std::vector<BorderLine> calculate_borders(const std::vector<PhysicalMonitor>& monitors);

private:
	std::vector<PhysicalMonitor> m_monitors;
};

constexpr BorderLine NULL_BORDER{ BorderLocation::NONE, 0 };


namespace mouse
{
	BorderLine get_closest_border();
};
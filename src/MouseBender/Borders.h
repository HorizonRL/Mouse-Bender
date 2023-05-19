#pragma once
#include "Mouse.h"
#include <vector>
#include <memory>


constexpr size_t NEAR_BORDER_MARGIN_PIXELS = 5;


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
	BorderType type;
	int location;
};

struct MonitorShape
{
	int left;
	int top;
	int right;
	int bottom;
};

struct PhysicalMonitor
{
	bool is_primary;
	MonitorShape shape;
};

namespace border_calculator
{
	std::vector<BorderLine> calc_borders();
};


constexpr BorderLine NULL_BORDER{ BorderLocation::NONE, BorderType::NONE, 0 };


class BorderHolder 
{
public:
	BorderHolder(BorderHolder const&) = delete;
	BorderHolder& operator=(BorderHolder const&) = delete;

public:
	static std::shared_ptr<BorderHolder> get_instance()
	{
		static std::shared_ptr<BorderHolder> instance{ new BorderHolder };
		return instance;
	}

public:
	std::vector<BorderLine> borders() const;

private:
	BorderHolder();

private:
	std::vector<BorderLine> m_borders;
};

namespace mouse
{
	BorderLine get_closest_border();
};
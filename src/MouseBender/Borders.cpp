#include "Borders.h"
#include <algorithm>


struct MonitorRects
{
    std::vector<RECT> rcMonitors;

    static BOOL CALLBACK MonitorEnum(HMONITOR hMon, HDC hdc, LPRECT lprcMonitor, LPARAM pData)
    {
        MonitorRects* pThis = reinterpret_cast<MonitorRects*>(pData);
        pThis->rcMonitors.push_back(*lprcMonitor);
        return TRUE;
    }

    MonitorRects()
    {
        EnumDisplayMonitors(
            0, 0,
            MonitorEnum, 
            (LPARAM)this
        );
    }
};


std::vector<BorderLine> border_calculator::calc_borders()
{
    MonitorRects raw_monitors_data;

    std::vector<int> left_positions;
    std::vector<int> right_positions;
    std::vector<int> bottom_positions;
    std::vector<int> top_positions;

    for (const RECT& monitor : raw_monitors_data.rcMonitors)
    {
        left_positions.emplace_back(monitor.left);
        right_positions.emplace_back(monitor.right);
        bottom_positions.emplace_back(monitor.bottom);
        top_positions.emplace_back(monitor.top);
    }

    BorderLine left_border{
        BorderLocation::LEFT,
        BorderType::VERTICAL,
        *std::min_element(left_positions.begin(), left_positions.end())
    };

    BorderLine right_border{
        BorderLocation::RIGHT,
        BorderType::VERTICAL,
        *std::max_element(right_positions.begin(), right_positions.end())
    };

    BorderLine bottom_border{
        BorderLocation::BOTTOM,
        BorderType::HORIZONTAL,
        *std::max_element(bottom_positions.begin(), bottom_positions.end())
    };

    BorderLine top_border{
        BorderLocation::TOP,
        BorderType::HORIZONTAL,
        *std::min_element(top_positions.begin(), top_positions.end())
    };

    return std::vector<BorderLine>{left_border, right_border, bottom_border, top_border};
}


BorderLine mouse::get_closest_border()
{
    auto borders = BorderHolder::get_instance()->borders();

    int real_time_pos = 0;
    Point real_time_mouse_point;
    bool is_close_border = false;
    size_t mouse_relative_size = 0;
    int border_margin = 0;


    for (const BorderLine& border : borders)
    {
        real_time_mouse_point = mouse::get_pos();

        switch (border.type)
        {
        case BorderType::HORIZONTAL:
            mouse_relative_size = mouse::get_height();
            real_time_pos = real_time_mouse_point.get_y();
            break;

        case BorderType::VERTICAL:
            mouse_relative_size = mouse::get_width();
            real_time_pos = real_time_mouse_point.get_x();
            break;

        default:
            continue;
        }

        switch (border.side)
        {
        case BorderLocation::RIGHT:
        case BorderLocation::BOTTOM:
            border_margin = border.location - static_cast<int>(mouse_relative_size);
            is_close_border = border_margin <= real_time_pos;
            break;

        case BorderLocation::LEFT:
        case BorderLocation::TOP:
            border_margin = border.location + static_cast<int>(mouse_relative_size);
            is_close_border = border_margin >= real_time_pos;
            break;

        default:
            continue;
        }

        if (is_close_border)
        {
            return border;
        }
    }

    return NULL_BORDER;
}

BorderHolder::BorderHolder()
    : m_borders(border_calculator::calc_borders())
{}

std::vector<BorderLine> BorderHolder::borders() const
{
    return m_borders;
}

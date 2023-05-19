#include "Borders.h"
#include <algorithm>


struct MonitorDataSupplier
{
    std::vector<MonitorShape> raw_monitors;

    static BOOL CALLBACK enumurate_monitors_callback(HMONITOR hMon, HDC hdc, LPRECT lprcMonitor, LPARAM pData)
    {
        MonitorDataSupplier* this_ptr = reinterpret_cast<MonitorDataSupplier*>(pData);
        MonitorShape shape{ lprcMonitor->left, lprcMonitor->top, lprcMonitor->right, lprcMonitor->bottom };
        this_ptr->raw_monitors.push_back(shape);
        return TRUE;
    }

    MonitorDataSupplier()
    {
        EnumDisplayMonitors(
            0, 0,
            enumurate_monitors_callback,
            reinterpret_cast<LPARAM>(this)
        );
    }
};

PhysicalMonitor::PhysicalMonitor(
    const MonitorShape& shape, const BorderLine& left_border, const BorderLine& top_border, 
    const BorderLine& right_border, const BorderLine& bottom_border)
    : BorderedMonitor(left_border, top_border, right_border, bottom_border)
    , m_shape(shape)
{}

bool PhysicalMonitor::is_inside() const
{
    const Point mouse_pos = mouse::get_pos();
    const bool is_in_x = mouse_pos.get_x() >= m_shape.left && mouse_pos.get_x() <= m_shape.right;
    const bool is_in_y = mouse_pos.get_y() >= m_shape.top && mouse_pos.get_y() <= m_shape.bottom;

    return is_in_x && is_in_y;
}

BorderedMonitor::BorderedMonitor(
    const BorderLine& left_border, const BorderLine& top_border, 
    const BorderLine& right_border, const BorderLine& bottom_border)
    : m_left_border(left_border)
    , m_top_border(top_border)
    , m_right_border(right_border)
    , m_bottom_border(bottom_border)
{}

BorderedMonitor::BorderedMonitor()
    : BorderedMonitor(NULL_BORDER, NULL_BORDER, NULL_BORDER, NULL_BORDER)
{}

BorderLine BorderedMonitor::get_left_border() const
{
    return m_left_border;
}

BorderLine BorderedMonitor::get_top_border() const
{
    return m_top_border;
}

BorderLine BorderedMonitor::get_right_border() const
{
    return m_right_border;
}

BorderLine BorderedMonitor::get_bottom_border() const
{
    return m_bottom_border;
}

std::vector<BorderLine> BorderedMonitor::get_borders() const
{
    return std::vector<BorderLine>{m_left_border, m_top_border, m_right_border, m_bottom_border};
}

MonitorsLayout::MonitorsLayout(const std::vector<PhysicalMonitor>& monitors)
{
}

std::vector<BorderLine> MonitorsLayout::calculate_borders(const std::vector<PhysicalMonitor>& monitors)
{
    return std::vector<BorderLine>();
}

//std::vector<BorderLine> border_calculator::calc_borders()
//{
//    MonitorDataSupplier raw_monitors_data;
//
//    std::vector<PhysicalMonitor> monitors;
//    for (const MonitorShape& monitor_shape : raw_monitors_data.raw_monitors)
//    {
//        monitors.emplace_back(
//            PhysicalMonitor{
//                monitor_shape,
//                BorderLine{BorderLocation::LEFT, monitor_shape.left},
//                BorderLine{BorderLocation::TOP, monitor_shape.top},
//                BorderLine{BorderLocation::RIGHT, monitor_shape.right},
//                BorderLine{BorderLocation::BOTTOM, monitor_shape.bottom}
//            }
//        );
//
//    }
//
//    return std::vector<BorderLine>{};
//}


//BorderLine mouse::get_closest_border()
//{
//
//    return NULL_BORDER;
//}

//BorderHolder::BorderHolder()
//    : m_borders(border_calculator::calc_borders())
//{}
//
//std::vector<BorderLine> BorderHolder::borders() const
//{
//    return m_borders;
//}
#include "task.hpp"

bool Task::operator<(const Task& other) const
{
    return priority < other.priority;
}

std::ostream& operator<<(std::ostream& os, const Task& t)
{
    os << "Task: " << t.name;
    os << ", Priority: " << t.priority;
    os << ", Assigned to: " << t.assigned_to;
    return os;
}
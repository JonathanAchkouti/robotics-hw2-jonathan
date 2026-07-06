#include <iostream>
#include <algorithm>

#include "robot.hpp"

Robot::Robot(const std::string& id, const std::string& name, int battery) :id_(id), name_(name), battery_(std::clamp(battery, 0, 100)), status_("idle"){}

void Robot::charge()
{
    battery_ = 100;
    status_ = "charging";
}

std::string Robot::id() const
{
    return id_;
}

std::string Robot::name() const
{
    return name_;
}

int Robot::battery() const
{
    return battery_;
}

std::string Robot::status() const
{
    return status_;
}

bool Robot::operator==(const Robot& other) const
{
    return id_ == other.id_;
}

std::string Robot::operator+(const Robot& other) const
{
    return name_ + " + " + other.name_;
}

std::ostream& operator<<(std::ostream& os, const Robot& r)
{
    os << "[" << r.type() << "] ";
    os << "ID: " << r.id_;
    os << ", Name: " << r.name_;
    os << ", Battery: " << r.battery_ << "%";
    os << ", Status: " << r.status_;
    return os;
}

void Robot::set_status(const std::string& status)
{
    status_ = status;
}

#include "cleaning_robot.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

CleaningRobot::CleaningRobot(const string& id, const string& name, int battery, double speed,double tank_capacity):MobileRobot(id, name, battery, speed),tank_capacity_(tank_capacity){}

void CleaningRobot::work()
{
    if (battery_ == 0) throw runtime_error(name_ + " cannot clean bcz the battery is empty");

    status_ = "working";
    battery_ = max(0, battery_ - 15);

    cout << name_ << " is cleaning with tank capacity ";
    cout << tank_capacity_ << " liters. Battery: ";
    cout << battery_ << "%" << endl;

    if (battery_ == 0) status_ = "idle";
}

string CleaningRobot::type() const
{
    return "CleaningRobot";
}
#include "cooking_robot.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

CookingRobot::CookingRobot(const string& id, const string& name,int battery, int recipes_count): Robot(id, name, battery),recipes_count_(recipes_count){}

void CookingRobot::work()
{
    if (battery_ == 0) throw runtime_error(name_ + " cannot cook: battery is empty");

    status_ = "working";
    battery_ = max(0, battery_ -25);

    cout << name_ << " is cooking. Recipes available: " << recipes_count_ << ". Battery: " << battery_ << "%" << endl;

    if (battery_ == 0) status_ = "idle";
}

string CookingRobot::type() const
{
    return "CookingRobot";
}
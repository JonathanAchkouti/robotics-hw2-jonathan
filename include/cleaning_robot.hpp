#pragma once

#include "mobile_robot.hpp"

#include <string>

class CleaningRobot : public MobileRobot {
public:
    CleaningRobot(const std::string& id, const std::string& name,int battery, double speed, double tank_capacity);

    void work() override;
    std::string type() const override;

private:
    double tank_capacity_;
};
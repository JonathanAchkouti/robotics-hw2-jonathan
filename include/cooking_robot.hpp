#pragma once

#include "robot.hpp"

#include <string>

class CookingRobot : public Robot {
public:
    CookingRobot(const std::string& id, const std::string& name, int battery, int recipes_count);

    void work() override;
    std::string type() const override;

private:
    int recipes_count_;
};
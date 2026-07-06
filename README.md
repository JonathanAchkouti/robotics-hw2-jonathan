# Robot Fleet Manager

This project is a C++ robot fleet management program for Homework 2. It uses object-oriented programming to model a fleet of robots, including a base `Robot` class and derived classes such as `MobileRobot`, `CleaningRobot`, and `CookingRobot`.

The program allows the user to add robots, remove robots, show all robots, make one robot work, make all robots work, charge all robots, assign tasks, show the task queue, and start timed work using a background thread.

## Main Features

- Abstract base class `Robot`
- Derived robot classes with overridden `work()` and `type()` methods
- `Fleet` which is the class that manages robots using smart pointers
- Task queue ordered by priority
- Operator overloading for `Robot`, `Task`, and `Fleet`
- Exception handling for invalid operations
- Background thread for timed work
- Interactive menu in `main.cpp`

## File Structure

robotics-hw2-jonathan/
├── include/
│   ├── robot.hpp
│   ├── mobile_robot.hpp
│   ├── cleaning_robot.hpp
│   ├── cooking_robot.hpp
│   ├── task.hpp
│   └── fleet.hpp
├── src/
│   ├── robot.cpp
│   ├── mobile_robot.cpp
│   ├── cleaning_robot.cpp
│   ├── cooking_robot.cpp
│   ├── task.cpp
│   └── fleet.cpp
├── main.cpp
├── compile.sh
├── README.md
├── ANSWERS.md
└── ENV_CHECK.md

## HOw to compile

`./compile.sh`
`g++ -std=c++17 -Wall -Wextra src/*.cpp main.cpp -I include -o fleet_app`

## How to run

`./fleet_app`
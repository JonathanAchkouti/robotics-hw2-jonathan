#!/bin/zsh

clang++ -std=c++17 -Wall -Wextra -pedantic -I include \
    main.cpp \
    src/cleaning_robot.cpp \
    src/cooking_robot.cpp \
    src/fleet.cpp \
    src/mobile_robot.cpp \
    src/robot.cpp \
    src/task.cpp \
    -o fleet_app

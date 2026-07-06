//ChatGPT helped me created most of the main for testing purposes (I understood it)

#include "cleaning_robot.hpp"
#include "cooking_robot.hpp"
#include "fleet.hpp"
#include "mobile_robot.hpp"

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>

void clear_input()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int read_int(const std::string& prompt)
{
    int value;

    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number.\n";
            clear_input();
            continue;
        }

        clear_input();
        return value;
    }
}

double read_double(const std::string& prompt)
{
    double value;

    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number.\n";
            clear_input();
            continue;
        }

        clear_input();
        return value;
    }
}

std::string read_string(const std::string& prompt)
{
    std::string value;

    std::cout << prompt;
    std::getline(std::cin, value);

    return value;
}

void show_menu()
{
    std::cout << "\n=== Robot Fleet Manager ===\n";
    std::cout << "1. Add robot\n";
    std::cout << "2. Remove robot\n";
    std::cout << "3. Show all robots\n";
    std::cout << "4. Work single robot\n";
    std::cout << "5. Work all\n";
    std::cout << "6. Charge all\n";
    std::cout << "7. Assign task to robot\n";
    std::cout << "8. Show task queue\n";
    std::cout << "9. Start timed work on a mobile robot\n";
    std::cout << "0. Exit\n";
}

void add_robot(Fleet& fleet)
{
    std::cout << "\nChoose robot type:\n";
    std::cout << "1. MobileRobot\n";
    std::cout << "2. CleaningRobot\n";
    std::cout << "3. CookingRobot\n";

    int type = read_int("Choice: ");

    std::string id = read_string("Robot id: ");
    std::string name = read_string("Robot name: ");
    int battery = read_int("Battery level: ");

    if (type == 1) {
        double speed = read_double("Speed: ");
        fleet += std::make_shared<MobileRobot>(id, name, battery, speed);
        std::cout << "MobileRobot added.\n";
        return;
    }

    if (type == 2) {
        double speed = read_double("Speed: ");
        double tank_capacity = read_double("Tank capacity: ");
        fleet += std::make_shared<CleaningRobot>(
            id, name, battery, speed, tank_capacity
        );
        std::cout << "CleaningRobot added.\n";
        return;
    }

    if (type == 3) {
        int recipes_count = read_int("Number of recipes: ");
        fleet += std::make_shared<CookingRobot>(
            id, name, battery, recipes_count
        );
        std::cout << "CookingRobot added.\n";
        return;
    }

    std::cout << "Invalid robot type.\n";
}

void remove_robot(Fleet& fleet)
{
    std::string id = read_string("Robot id to remove: ");
    fleet -= id;
    std::cout << "Robot removed.\n";
}

void work_single_robot(Fleet& fleet)
{
    std::string id = read_string("Robot id to work: ");
    auto robot = fleet.find(id);
    robot->work();
}

void assign_task(Fleet& fleet)
{
    std::string robot_id = read_string("Robot id: ");
    std::string task_name = read_string("Task name: ");
    int priority = read_int("Priority from 1 to 5: ");

    if (priority < 1 || priority > 5) {
        std::cout << "Priority must be between 1 and 5.\n";
        return;
    }

    Task task;
    task.name = task_name;
    task.priority = priority;
    task.assigned_to = robot_id;

    fleet.assign_task(robot_id, task);
}

void start_timed_work(Fleet& fleet)
{
    std::string id = read_string("Mobile robot id: ");
    int seconds = read_int("Number of seconds: ");

    auto robot = fleet.find(id);

    auto mobile = std::dynamic_pointer_cast<MobileRobot>(robot);

    if (mobile == nullptr) {
        std::cout << "This robot is not a MobileRobot.\n";
        return;
    }

    mobile->start_work(seconds);
    std::cout << "Timed work started.\n";
}

int main()
{
    Fleet fleet;

    bool running = true;

    while (running) {
        show_menu();

        int choice = read_int("Choice: ");

        try {
            if (choice == 1) {
                add_robot(fleet);
            } else if (choice == 2) {
                remove_robot(fleet);
            } else if (choice == 3) {
                std::cout << fleet;
            } else if (choice == 4) {
                work_single_robot(fleet);
            } else if (choice == 5) {
                fleet.work_all();
            } else if (choice == 6) {
                fleet.charge_all();
            } else if (choice == 7) {
                assign_task(fleet);
            } else if (choice == 8) {
                fleet.show_tasks();
            } else if (choice == 9) {
                start_timed_work(fleet);
            } else if (choice == 0) {
                running = false;
            } else {
                std::cout << "Invalid choice.\n";
            }
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    std::cout << "Goodbye.\n";

    return 0;
}
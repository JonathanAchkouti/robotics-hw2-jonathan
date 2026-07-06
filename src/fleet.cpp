#include "fleet.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

void Fleet::add(shared_ptr<Robot> robot)
{
    if (!robot) throw runtime_error("Cannot add a null robot");
    robots_[robot->id()] = robot;
}

void Fleet::remove(const string& id)
{
    auto erased = robots_.erase(id);
    if (erased == 0) throw runtime_error("The robot having the id " + id + " was unfortunately not found");
}

shared_ptr<Robot> Fleet::find(const string& id) const
{
    auto it = robots_.find(id);
    if (it == robots_.end()) throw runtime_error("Robot with id " + id + " was not found");
    return it->second;
}

void Fleet::assign_task(const string& robot_id, const Task& t)
{
    auto robot = find(robot_id);
    Task task = t;
    task.assigned_to = robot_id;
    tasks_.push(task);
    robot->set_status("working");

    cout << "Assigned task to " << robot->name() << ": "<< task.name << endl;
}

void Fleet::show_tasks() const
{
    if (tasks_.empty())
    {
        cout << "No tasks in the queue." <<endl;
        return;
    }

    auto copy = tasks_;

    cout << "Task queue:" << endl;

    while (!copy.empty()) {
        cout << copy.top() << endl;
        copy.pop();
    }
}

void Fleet::work_all() const
{
    if (robots_.empty())
    {
        cout << "No robots in the fleet.\n";
        return;
    }

    for (const auto& pair : robots_) {
        try{
            pair.second->work();
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}

void Fleet::charge_all() const
{
    if (robots_.empty())
    {
        cout << "Fleet empty." << endl;
        return;
    }

    for (const auto& pair : robots_) pair.second->charge();

    cout << "All robots charged." << endl;
}

size_t Fleet::size() const
{
    return robots_.size();
}

bool Fleet::empty() const
{
    return robots_.empty();
}

Fleet& Fleet::operator+=(shared_ptr<Robot> robot)
{
    add(robot);
    return *this;
}

Fleet& Fleet::operator-=(const string& id)
{
    remove(id);
    return *this;
}

ostream& operator<<(ostream& os, const Fleet& f)
{
    os << "Fleet:";

    if (f.robots_.empty())
    {
        os << "No robots in the fleet.\n";
        return os;
    }

    for (const auto& pair: f.robots_)os << *(pair.second) << endl;

    vector<shared_ptr<Robot>> robots;

    for (const auto& pair : f.robots_) robots.push_back(pair.second);

    auto low_battery = find_if
    (
        robots.begin(),
        robots.end(),
        [](const shared_ptr<Robot>& robot) {
            return robot->battery() < 20;
        }
    );

    if (low_battery != robots.end()) os << "First robot battery under 20%: "<< (*low_battery)->name() << endl;
    else os << "No robot below 20% battery."<< endl;
    return os;
}
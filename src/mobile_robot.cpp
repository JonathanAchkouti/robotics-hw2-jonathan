#include "mobile_robot.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

using namespace std;

MobileRobot::MobileRobot(const string& id, const string& name, int battery, double speed): Robot(id, name, battery),speed_(speed) {}

MobileRobot::~MobileRobot()
{
    stop_ = true;
    if (worker_.joinable()) worker_.join();
}

void MobileRobot::work()
{
    if (battery_ == 0) throw runtime_error(name_ + " cannot work: battery is empty");
    status_ = "working";
    battery_ = max(0, battery_ - 20);
    cout << name_ << " is moving at speed "<< speed_ << " m/s. Battery: "<< battery_ << "%" << endl;

    if (battery_ == 0) status_ = "idle";
}

string MobileRobot::type() const
{
    return "MobileRobot";
}

void MobileRobot::start_work(int seconds)
{
    if (seconds <= 0) throw runtime_error("Timed work duration must be positive");

    stop_ = false;

    if (worker_.joinable()) worker_.join();

    worker_ = thread([this, seconds]() {
        for (int i = 0; i < seconds && !stop_; ++i) {
            try {
                work();
                cout << *this << endl;
            } catch (const runtime_error& e) {
                cout << "Error: " << e.what() << endl;
                stop_ = true;
            }
            this_thread::sleep_for(chrono::seconds(1));
        }
        status_ = "idle";
    });
}
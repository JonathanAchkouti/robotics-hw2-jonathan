## 1.

I used `std::shared_ptr<Robot>` because if I used `unique_ptr`, ownership would belong to only one place, so copying or sharing robot pointers cannot be done. I would need to use `std::move`, and some parts of the code that pass robots around would become more difficult.

## 2. 

I used `std::unordered_map<std::string, std::shared_ptr<Robot>>`. The key is the robot id, and the value is the robot pointer. This is useful because robots need to be found quickly by id. The average lookup cost is O(1), which is faster than searching through a vector one by one (O(n)) (Also no need for an ordered so we kind of bypassed the O(log(n)) insertions for an amortized O(1)).

## 3. 

I used `std::priority_queue<Task>`. It is usually built on top of a vector and internally keeps the highest-priority element at the top using heap behavior. This only makes sense because whenever I show or process tasks, the task with the highest priority should come first.

## 4.

`friend` gives the function access to the private or protected data members of the class. This is useful because `operator<<` is not a member of `Robot`.

It cannot be a regular member function because the left hand side of the operator (which is the caller) is `std::ostream`, not a `Robot`. 

## 5.

Using `std::find_if` with a lambda shows that I am searching for the first element that satisfies a condition. The lambda contains only the condition. A hand-written loop also, but it is less direct.

## 6. `work()` throws if battery is 0. Why use an exception rather than returning false or printing an error?

Throwing an exception separates the error handling from the normal logic. It also lets the caller decide how to handle the problem.

## 7.

Yes, the fleet remains consistent. `assign_task` first calls `find(robot_id)`. If the robot does not exist, `find()` throws before the task is pushed into the priority queue. This means no task is added for a robot that does not exist, so the fleet state stays valid.

## 8.

I used `worker_` to store the background thread. The thread calls `work()` once per second (the number of seconds requested). I used `stop_` as a flag that can stop the loop early if needed (for e.g. in case if the battery becomes empty).

Before starting a new thread, I check if the previous thread is joinable and join it. In the destructor, I set `stop_` to true and join the thread if it is still running. This avoids leaving a background thread running after the object is destroyed.

## 9.

The code does not compile because `MaintenanceRobot` inherits from both `MobileRobot` and `CookingRobot`, and both of those inherit from `Robot`. This means `MaintenanceRobot` contains two separate copies of the `Robot` base class.

So when we run:

    std::cout << m.name_;

C++ does not know which `name_` to use

This problem is solved using virtual inheritance. The keyword is `virtual`.

Corrected version:

    #include <iostream>
    #include <string>

    class Robot {
    public:
        std::string name_ = "base";
    };

    class MobileRobot : virtual public Robot {
    };

    class CookingRobot : virtual public Robot {
    };

    class MaintenanceRobot : public MobileRobot, public CookingRobot {
    };

    int main() {
        MaintenanceRobot m;
        std::cout << m.name_ << "\n";
    }

With `virtual public Robot`, C++ keeps only one shared copy of the `Robot` base class inside `MaintenanceRobot`. With `virtual public Robot`, we tell the compiler that MobileRobot and CookingRobot should share the same Robot base class instead of each having their own separate copy. This prevents ambiguity because MaintenanceRobot now contains only one Robot::name_.
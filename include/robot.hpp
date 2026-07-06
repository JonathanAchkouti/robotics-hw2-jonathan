#pragma once
#include <string>
#include <ostream>


struct Task;

class Robot {
public:
    Robot(const std::string& id, const std::string& name, int battery);
    virtual ~Robot() = default;

    virtual void        work()  = 0;  // uses battery, sets status to "working"
    virtual void        charge();     // restores battery to 100
    virtual std::string type()  const = 0;

    std::string id()      const;
    std::string name()    const;
    int         battery() const;
    std::string status()  const;
    void set_status(const std::string& status);

    bool operator==(const Robot& other) const;

    // Returns e.g. "R2D2 + C3PO"
    std::string operator+(const Robot& other) const;

    /* It is not a regular method, because usually, the left-hand side of the operator calls 
    the function, so here the left-hand side is cout which is not a an instance of the class.
    We need friend for the function to access the private and protected data members.*/
    friend std::ostream& operator<<(std::ostream& os, const Robot& r);

protected:
    std::string id_;
    std::string name_;
    int         battery_;  // always clamped to [0, 100]
    std::string status_;   // "idle" | "working" | "charging"
};

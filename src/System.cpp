#include "System.h"
#include "Vector.h"
#include "StringTool.h"
#include <utility>
#include <sstream>

using namespace std;

System::System(std::string name, long double time) : time(time),
                                                     name(std::move(name)) {}

void System::AddObject(const std::string &object_name, long double GM,
                       long double X, long double Y, long double Z,
                       long double VX, long double VY, long double VZ) {
    objects.push_back(new Body(object_name, GM, X, Y, Z, VX, VY, VZ));

}

std::string System::get_name() const {
    return name;
}

long double System::get_time() const {
    return time;
}

string System::Output() const {
    stringstream ss;
    ss << name << " " << string_tool::PreciseOut(time);
    for (Body *object:objects) {
        ss << "\n" << object->Output();
    }
    return ss.str();
}

System::~System() {
    for (Body *object:objects) {
        delete object;
    }
    objects.clear();
}

const std::vector<Body *> &System::get_objects() {
    return objects;
}

void System::AddTime(long double step) {
    time += step;
}

string System::TableString() const {
    stringstream ss;
    ss << "(" << name << ", T = " << time;
    if (objects.empty()) {
        ss << ", empty)";
        return ss.str();
    } else {
        ss << ")\n";
    }
    ss
            << "BODY         |           GM |            X |            Y |            Z |           VX |           VY |           VZ\n";
    ss
            << "-------------+--------------+--------------+--------------+--------------+--------------+--------------+-------------";
    for (Body *object:objects) {
        ss << "\n" << object->TableString();
    }
    return ss.str();
}

//
// Created by Yifei Yao on 8/14/21.
//

#include "System.h"
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

std::ostream &operator<<(ostream &os, const System &aSystem) {
    os << aSystem.name << " T = " << aSystem.time;
    for (Body *object:aSystem.objects) {
        os << "\n" << *object;
    }
    return os;
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

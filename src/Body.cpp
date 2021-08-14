//
// Created by Yifei Yao on 8/14/21.
//

#include "Body.h"

#include <utility>

using namespace std;

Body::Body(std::string name, long double GM,
           long double X, long double Y, long double Z,
           long double VX, long double VY, long double VZ) :
        name(std::move(name)),
        GM(GM),
        position(X, Y, Z),
        velocity(VX, VY, VZ) {}

std::ostream &operator<<(ostream &os, const Body &object) {
    os << object.name << " GM = " << object.GM;
    os << " X = " << object.position.get_x();
    os << " Y = " << object.position.get_y();
    os << " Z = " << object.position.get_z();
    os << " VX = " << object.position.get_x();
    os << " VY = " << object.position.get_x();
    os << " VZ = " << object.position.get_x();
    return os;
}

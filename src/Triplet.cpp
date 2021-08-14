//
// Created by Yifei Yao on 8/14/21.
//

#include "Triplet.h"
#include "StringTool.h"
#include <sstream>

using namespace string_tool;
Triplet::Triplet(long double x, long double y, long double z) : x(x), y(y),
                                                                z(z) {}

long double Triplet::get_x() const {
    return x;
}

long double Triplet::get_y() const {
    return y;
}

long double Triplet::get_z() const {
    return z;
}

std::string Triplet::Output() const {
    std::stringstream ss;
    ss << PreciseOut(x) << " " << PreciseOut(y) << " " << PreciseOut(z);
    return ss.str();
}
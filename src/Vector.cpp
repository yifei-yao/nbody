#include "Vector.h"
#include "StringTool.h"
#include <sstream>

using namespace string_tool;

Vector::Vector(long double x, long double y, long double z) : x(x), y(y),
                                                              z(z) {}

long double Vector::get_x() const {
    return x;
}

long double Vector::get_y() const {
    return y;
}

long double Vector::get_z() const {
    return z;
}

std::string Vector::Output() const {
    std::stringstream ss;
    ss << PreciseOut(x) << " " << PreciseOut(y) << " " << PreciseOut(z);
    return ss.str();
}

Vector operator-(const Vector &lhs, const Vector &rhs) {
    return Vector{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

long double Vector::SumOfSquares() const {
    return x * x + y * y + z * z;
}

void Vector::operator+=(const Vector &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
}

Vector operator*(const Vector &lhs, long double scalar) {
    return Vector{lhs.x * scalar, lhs.y * scalar, lhs.z * scalar};
}

Vector operator+(const Vector &lhs, const Vector &rhs) {
    return Vector{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

void Vector::operator*=(long double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

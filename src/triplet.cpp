#include "triplet.h"
#include "string_tool.h"
#include <sstream>

using namespace string_tool;

Triplet::Triplet(long double x, long double y, long double z) : x(x), y(y),
                                                                z(z) {}

long double Triplet::GetX() const {
  return x;
}

long double Triplet::GetY() const {
  return y;
}

long double Triplet::GetZ() const {
  return z;
}

std::string Triplet::Output() const {
  std::stringstream ss;
  ss << PreciseOut(x) << " " << PreciseOut(y) << " " << PreciseOut(z);
  return ss.str();
}

Triplet operator-(const Triplet &lhs, const Triplet &rhs) {
  return Triplet{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

long double Triplet::SumOfSquares() const {
  return x * x + y * y + z * z;
}

void Triplet::operator+=(const Triplet &rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
}

Triplet operator*(const Triplet &lhs, long double scalar) {
  return Triplet{lhs.x * scalar, lhs.y * scalar, lhs.z * scalar};
}

Triplet operator+(const Triplet &lhs, const Triplet &rhs) {
  return Triplet{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

void Triplet::operator*=(long double scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
}

void Triplet::operator-=(const Triplet &rhs) {
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
}

void Triplet::operator/=(long double scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
}

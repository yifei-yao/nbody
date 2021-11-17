#include "body.h"
#include "string_tool.h"
#include <utility>
#include <sstream>
#include <iomanip>

using namespace std;

Body::Body(std::string name, long double GM,
           long double X, long double Y, long double Z,
           long double VX, long double VY, long double VZ) :
        name(std::move(name)),
        GM(GM),
        position(X, Y, Z),
        velocity(VX, VY, VZ) {}

string Body::Output() const {
  stringstream ss;
  ss << name << " " << string_tool::PreciseOut(GM) << " " << position.Output()
     << " " << velocity.Output();
  return ss.str();
}

const Triplet &Body::GetPosition() const {
  return position;
}

const Triplet &Body::GetVelocity() const {
  return velocity;
}

long double Body::GetGM() const {
  return GM;
}

void Body::AddBuffer(const Triplet &triplet) {
  buffer.push_back(triplet);
}

void Body::AddPosition(const Triplet &triplet) {
  position += triplet;
}

void Body::AddVelocity(const Triplet &triplet) {
  velocity += triplet;
}

const Triplet &Body::GetBuffer(int index) const {
  return buffer[index];
}

void Body::ClearBuffer() {
  buffer.clear();
}

const Triplet &Body::GetBufV(size_t index) const {
  return buffer[3 * index];
}

const Triplet &Body::GetBufA(size_t index) const {
  return buffer[3 * index + 2];
}

const Triplet &Body::GetBufXLast() const {
  size_t n = buffer.size();
  return buffer[(n - 1) / 3 * 3 + 1];
}

std::string Body::TableString() const {
  stringstream ss;
  ss << setw(12) << left << name.substr(0, 12);
  ss << " | " << setw(12) << right << GM;
  ss << " | " << setw(12) << right << position.GetX();
  ss << " | " << setw(12) << right << position.GetY();
  ss << " | " << setw(12) << right << position.GetZ();
  ss << " | " << setw(12) << right << velocity.GetX();
  ss << " | " << setw(12) << right << velocity.GetY();
  ss << " | " << setw(12) << right << velocity.GetZ();
  return ss.str();
}


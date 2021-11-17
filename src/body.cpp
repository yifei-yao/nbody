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

const Triplet &Body::get_position() const {
  return position;
}

const Triplet &Body::get_velocity() const {
  return velocity;
}

long double Body::get_GM() const {
  return GM;
}

void Body::AddBuffer(const Triplet &triplet) {
  buffer.push_back(triplet);
}

void Body::add_position(const Triplet &triplet) {
  position += triplet;
}

void Body::add_velocity(const Triplet &triplet) {
  velocity += triplet;
}

const Triplet &Body::get_buffer(int index) const {
  return buffer[index];
}

void Body::ClearBuffer() {
  buffer.clear();
}

const Triplet &Body::get_buf_v(size_t index) const {
  return buffer[3 * index];
}

const Triplet &Body::get_buf_a(size_t index) const {
  return buffer[3 * index + 2];
}

const Triplet &Body::get_buf_x_last() const {
  size_t n = buffer.size();
  return buffer[(n - 1) / 3 * 3 + 1];
}

std::string Body::TableString() const {
  stringstream ss;
  ss << setw(12) << left << name.substr(0, 12);
  ss << " | " << setw(12) << right << GM;
  ss << " | " << setw(12) << right << position.get_x();
  ss << " | " << setw(12) << right << position.get_y();
  ss << " | " << setw(12) << right << position.get_z();
  ss << " | " << setw(12) << right << velocity.get_x();
  ss << " | " << setw(12) << right << velocity.get_y();
  ss << " | " << setw(12) << right << velocity.get_z();
  return ss.str();
}


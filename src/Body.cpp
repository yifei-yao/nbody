#include "Body.h"
#include "StringTool.h"
#include <utility>
#include <sstream>

using namespace std;

Body::Body(std::string name, long double GM,
           long double X, long double Y, long double Z,
           long double VX, long double VY, long double VZ) :
        name(std::move(name)),
        GM(GM),
        position(X, Y, Z),
        velocity(VX, VY, VZ) {}

ostream &operator<<(ostream &os, const Body &object) {
    os << object.name << " GM = " << object.GM;
    os << " X = " << object.position.get_x();
    os << " Y = " << object.position.get_y();
    os << " Z = " << object.position.get_z();
    os << " VX = " << object.velocity.get_x();
    os << " VY = " << object.velocity.get_y();
    os << " VZ = " << object.velocity.get_z();
    return os;
}

string Body::Output() const {
    stringstream ss;
    ss << name << " " << string_tool::PreciseOut(GM) << " " << position.Output()
       << " " << velocity.Output();
    return ss.str();
}

const Vector &Body::get_position() const {
    return position;
}

const Vector &Body::get_velocity() const {
    return velocity;
}

long double Body::get_GM() const {
    return GM;
}

void Body::AddBuffer(const Vector &vector) {
    buffer.push_back(vector);
}

void Body::add_position(const Vector &vector) {
    position += vector;
}

void Body::add_velocity(const Vector &vector) {
    velocity += vector;
}

const Vector &Body::get_buffer(int index) const {
    return buffer[index];
}

void Body::ClearBuffer() {
    buffer.clear();
}

const std::string &Body::get_name() const {
    return name;
}

const Vector &Body::get_buf_v(size_t index) const {
    return buffer[3 * index];
}

const Vector &Body::get_buf_a(size_t index) const {
    return buffer[3 * index + 2];
}

const Vector &Body::get_buf_x_last() const {
    size_t n = buffer.size();
    return buffer[(n - 1) / 3 * 3 + 1];
}
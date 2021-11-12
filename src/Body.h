#ifndef BODY_H
#define BODY_H

#include "Vector.h"
#include <string>
#include <iostream>
#include <vector>


class Body {
public:
    Body(std::string name, long double,
         long double, long double, long double,
         long double, long double, long double);

    [[nodiscard]] std::string Output() const;

    [[nodiscard]] std::string TableString() const;

    [[nodiscard]] std::string SingleString() const;

    [[nodiscard]] const Vector &get_position() const;

    [[nodiscard]] const Vector &get_velocity() const;

    [[nodiscard]] const std::string &get_name() const;

    void add_position(const Vector &);

    void add_velocity(const Vector &);

    [[nodiscard]] long double get_GM() const;

    void AddBuffer(const Vector &);

    [[nodiscard]] const Vector &get_buffer(int) const;

    void ClearBuffer();

    [[nodiscard]] const Vector &get_buf_x_last() const;

    [[nodiscard]] const Vector &get_buf_v(size_t) const;

    [[nodiscard]] const Vector &get_buf_a(size_t) const;

private:
    std::string name;

    long double GM; //Gravitational parameter (gravitational constant * mass)
    Vector position;
    Vector velocity;
    std::vector<Vector> buffer;
};

#endif //BODY_H
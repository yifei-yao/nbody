#ifndef BODY_H
#define BODY_H

#include "Vector.h"
#include <string>
#include <iostream>
#include <vector>


class Body {
    friend std::ostream &operator<<(std::ostream &, const Body &);

public:
    Body(std::string name, long double,
         long double, long double, long double,
         long double, long double, long double);

    std::string Output() const;

    const Vector &get_position() const;

    const Vector &get_velocity() const;

    const std::string &get_name() const;

    void add_position(const Vector &);

    void add_velocity(const Vector &);

    long double get_GM() const;

    void AddBuffer(const Vector &);

    const Vector &get_buffer(int) const;

    void ClearBuffer();

    void push_buf_x(const Vector &);

    void push_buf_v(const Vector &);

    void push_buf_a(const Vector &);

    const Vector &get_buf_x(size_t) const;

    const Vector &get_buf_x_last() const;

    const Vector &get_buf_v(size_t) const;

    const Vector &get_buf_v_last() const;

    const Vector &get_buf_a(size_t) const;

    const Vector &get_buf_a_last() const;


    void clear_all_buf();


private:
    std::string name;

    long double GM; //Gravitational parameter (gravitational constant * mass)
    Vector position;
    Vector velocity;
    std::vector<Vector> buffer;

    std::vector<Vector> buf_x;
    std::vector<Vector> buf_v;
    std::vector<Vector> buf_a;
};

#endif //BODY_H
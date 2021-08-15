//
// Created by Yifei Yao on 8/14/21.
//
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

    void add_position(const Vector &);

    void add_velocity(const Vector &);

    long double get_GM() const;

    void AddBuffer(const Vector &);

    const Vector &get_buffer(int) const;

    void ClearBuffer();

private:
    std::string name;
    long double GM; //Gravitational parameter (gravitational constant * mass)
    Vector position;
    Vector velocity;
    std::vector<Vector> buffer;
};


#endif //BODY_H

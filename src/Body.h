//
// Created by Yifei Yao on 8/14/21.
//
#ifndef BODY_H
#define BODY_H

#include "Triplet.h"
#include <string>
#include <iostream>

class Body {
    friend std::ostream &operator<<(std::ostream &, const Body &);

public:
    Body(std::string name, long double,
         long double, long double, long double,
         long double, long double, long double);

    std::string Output() const;

private:
    std::string name;
    long double GM; //Gravitational parameter (gravitational constant * mass)
    Triplet position;
    Triplet velocity;
};


#endif //BODY_H

//
// Created by Yifei Yao on 8/14/21.
//
#ifndef BODY_H
#define BODY_H

#include "Triplet.h"
#include <string>

class Body {
public:
    Body(long double, Triplet, Triplet, std::string);

private:
    long double GM; //Gravitational parameter (gravitational constant * mass)
    Triplet position;
    Triplet velocity;
    std::string name;
};


#endif //BODY_H

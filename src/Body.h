//
// Created by Yifei Yao on 8/14/21.
//
#ifndef BODY_H
#define BODY_H

#include "Triplet.h"

class Body {
public:
    Body(long double, Triplet, Triplet);

private:
    long double GM; //Gravitational parameter (gravitational constant * mass)
    Triplet position;
    Triplet velocity;
};


#endif //BODY_H

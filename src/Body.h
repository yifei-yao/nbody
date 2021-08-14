//
// Created by Yifei Yao on 8/14/21.
//
#ifndef NBODY_BODY_H
#define NBODY_BODY_H

#include "Triplet.h"

class Body {
public:
    Body(long double, Triplet, Triplet);

private:
    long double GM; //Gravitational parameter (gravitational constant * mass)
    Triplet position;
    Triplet velocity;
};


#endif //NBODY_BODY_H

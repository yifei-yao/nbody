//
// Created by Yifei Yao on 8/14/21.
//

#ifndef NBODY_SYSTEM_H
#define NBODY_SYSTEM_H

#include "Body.h"
#include "vector"

class System {
public:
    explicit System(long double time);

private:
    long double time;
    std::vector<Body *> objects;
};


#endif //NBODY_SYSTEM_H

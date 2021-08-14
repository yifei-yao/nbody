//
// Created by Yifei Yao on 8/14/21.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include "Body.h"
#include "vector"

class System {
public:
    explicit System(long double time);

private:
    long double time;
    std::vector<Body *> objects;
};


#endif //SYSTEM_H

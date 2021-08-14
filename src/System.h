//
// Created by Yifei Yao on 8/14/21.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include "Body.h"
#include "vector"

class System {
public:
    explicit System(long double time, std::string name);

    void AddObject(Body);

private:
    long double time;
    std::vector<Body *> objects;
    std::string name;
};


#endif //SYSTEM_H

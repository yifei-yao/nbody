//
// Created by Yifei Yao on 8/14/21.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include "Body.h"
#include "vector"

class System {
public:
    explicit System(std::string name, long double time);

    void
    AddObject(const std::string &object_name, long double,
              long double, long double, long double,
              long double, long double, long double);

private:
    std::string name;
    long double time;
    std::vector<Body *> objects;
};


#endif //SYSTEM_H

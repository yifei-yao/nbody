//
// Created by Yifei Yao on 8/14/21.
//

#ifndef ENGINE_H
#define ENGINE_H

#include "System.h"

class Engine {
public:
    Engine();

    void AddTarget(const std::string & = std::string(), long double = 0);

    bool
    AddObject(const std::string &, long double,
              long double, long double, long double,
              long double, long double, long double);

    bool PrintTarget() const;

private:
    System *target;
};


#endif //ENGINE_H

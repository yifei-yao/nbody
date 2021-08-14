//
// Created by Yifei Yao on 8/14/21.
//

#ifndef ENGINE_H
#define ENGINE_H

#include "System.h"

class Engine {
public:
    Engine();

    ~Engine();

    void AddTarget(const std::string & = std::string(), long double = 0);

    bool
    AddObject(const std::string &, long double,
              long double, long double, long double,
              long double, long double, long double);

    bool PrintTarget() const;

    bool Save(const std::string &);

    bool Load(const std::string &);

private:
    System *target;
};


#endif //ENGINE_H

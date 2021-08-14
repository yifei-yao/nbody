//
// Created by Yifei Yao on 8/14/21.
//

#include "Engine.h"
#include "iostream"

using namespace std;

Engine::Engine() : target(nullptr) {}

void Engine::AddTarget(const std::string &name, long double time) {
    delete target;
    target = new System(name, time);
}

bool
Engine::AddObject(const string &name, long double GM,
                  long double X, long double Y, long double Z,
                  long double VX, long double VY, long double VZ) {
    if (target == nullptr) { return false; }
    target->AddObject(name, GM, X, Y, Z, VX, VY, VZ);
    return true;
}

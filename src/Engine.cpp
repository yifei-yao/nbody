//
// Created by Yifei Yao on 8/14/21.
//

#include "Engine.h"
#include <iostream>
#include <fstream>

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

bool Engine::PrintTarget() const {
    if (target == nullptr) {
        cout << "Target is empty!\n";
        return false;
    }
    cout << *target;
    return true;
}

bool Engine::Save(const string &path) {
    if (target == nullptr) { return false; }
    fstream file;
    file.open(path, ios::out);
    if (!file) { return false; }
    file << target->Output();
    file.close();
    return true;
}

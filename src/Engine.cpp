#include "Engine.h"
#include "Solver.h"
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
    cout << *target << "\n";
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

Engine::~Engine() {
    delete target;
}

bool Engine::Load(const string &path) {
    fstream file;
    file.open(path, ios::in);
    if (!file) { return false; }
    string name;
    long double time;
    if (file >> name >> time) {
        delete target;
        target = new System(name, time);
        string object_name;
        long double GM;
        long double X, Y, Z, VX, VY, VZ;
        while (file >> object_name >> GM >> X >> Y >> Z >> VX >> VY >> VZ) {
            AddObject(object_name, GM, X, Y, Z, VX, VY, VZ);
        }
        file.close();
        return true;
    } else {
        file.close();
        return false;
    }
}

bool Engine::Run(long double end, long double time_limit, const string &method,
                 const string &log_path, bool verbose) {
    if (target == nullptr) { return false; }
    if (end <= target->get_time()) { return false; }
    if (method == "Euler") {
        Euler solver(target);
        StepScheduler(solver, end, time_limit);
    }
    if (method == "EulerImproved") {
        EulerImproved solver(target);
        StepScheduler(solver, end, time_limit);
    }
    if (method == "RK4") {
        RK4 solver(target);
        StepScheduler(solver, end, time_limit);
    }
    cout << *target << "\n";
    return true;
}
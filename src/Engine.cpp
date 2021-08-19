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
    if (method == "RK4Example") {
        RK4Example solver(target);
        StepScheduler(solver, end, time_limit);
    }
    if (method == "Ralston4") {
        Ralston4 solver(target);
        StepScheduler(solver, end, time_limit);
    }
    cout << *target << "\n";
    return true;
}

bool
Engine::Translate(const string &from, long double X, long double Y,
                  long double Z,
                  long double VX, long double VY, long double VZ) {
    if (target == nullptr) { return false; }
    Vector from_position = Vector();
    Vector from_velocity = Vector();
    Vector to_position = Vector(X, Y, Z);
    Vector to_velocity = Vector(VX, VY, VZ);
    for (Body *object: target->get_objects()) {
        if (object->get_name() == from) {
            from_position = object->get_position();
            from_velocity = object->get_velocity();
            DoTranslation(from_position, from_velocity, to_position,
                          to_velocity);
            return true;
        }
    }
    if (from == "Barycenter") {
        CalculateBarycenter(from_position, from_velocity);
        DoTranslation(from_position, from_velocity, to_position, to_velocity);
        return true;
    }
    if (from == "Origin") {
        DoTranslation(from_position, from_velocity, to_position, to_velocity);
        return true;
    }
    return false;
}

void
Engine::DoTranslation(const Vector &from_position, const Vector &from_velocity,
                      const Vector &to_position, const Vector &to_velocity) {
    Vector delta_x = to_position - from_position;
    Vector delta_v = to_velocity - from_velocity;
    for (Body *object: target->get_objects()) {
        object->add_position(delta_x);
        object->add_velocity(delta_v);
    }
}

void Engine::CalculateBarycenter(Vector &position, Vector &velocity) {
    long double total_GM = 0;
    position = Vector();
    velocity = Vector();
    for (Body *object: target->get_objects()) {
        total_GM += object->get_GM();
        position += object->get_position() * object->get_GM();
        velocity += object->get_velocity() * object->get_GM();
    }
    if (total_GM != 0) {
        position /= total_GM;
        velocity /= total_GM;
    }
}

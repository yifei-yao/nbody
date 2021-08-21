#include "Engine.h"
#include "Solver.h"
#include "StringTool.h"
#include <iostream>
#include <fstream>
#include <thread>

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
    cout << target->TableString() << "\n";
    return true;
}

bool Engine::Save(const string &path) const {
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
    if (time_limit <= 0) { return false; }
    fstream file;
    file.open(log_path, ios::app);
    bool log_flag(file);
    file.close();
    thread log_thread;
    if (log_flag) {
        log_thread = thread(&Engine::Log, this, end, log_path);
    }
    thread output_thread;
    if (verbose) {
        output_thread = thread(&Engine::RealtimePrint, this, end);
    } else {
        output_thread = thread(&Engine::PrintProgressBar, this, end);
    }
    if (method == "Euler") {
        Euler solver(target);
        StepScheduler(solver, end, time_limit);
    } else if (method == "EulerImproved") {
        EulerImproved solver(target);
        StepScheduler(solver, end, time_limit);
    } else if (method == "Ralston4") {
        Ralston4 solver(target);
        StepScheduler(solver, end, time_limit);
    } else {
        RK4 solver(target);
        StepScheduler(solver, end, time_limit);
    }
    output_thread.join();
    if (log_flag) {
        log_thread.join();
    }
    cout << target->TableString() << "\n";
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
        DoTranslation(from_position, from_velocity, to_position,
                      to_velocity);
        return true;
    }
    if (from == "Origin") {
        DoTranslation(from_position, from_velocity, to_position,
                      to_velocity);
        return true;
    }
    return false;
}

void
Engine::DoTranslation(const Vector &from_position,
                      const Vector &from_velocity,
                      const Vector &to_position,
                      const Vector &to_velocity) {
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

void Engine::PrintProgressBar(long double end) const {
    long double total = end - target->get_time();
    long double start = target->get_time();
    while (end > target->get_time()) {
        cout << "[";
        long double portion = (target->get_time() - start) / total;
        int progress = portion * 60;
        for (int i = 0; i < progress; ++i) {
            cout << "=";
        }
        cout << ">";
        for (int i = 0; i < 60 - progress; ++i) {
            cout << " ";
        }
        cout << "]  " << string_tool::PercentageOut(portion) << " % \r";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void Engine::RealtimePrint(long double end) const {
    while (end > target->get_time()) {
        cout << target->TableString() << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void Engine::Log(long double end, const string &path) const {
    while (end > target->get_time()) {
        fstream file;
        file.open(path, ios::app);
        if (file) {
            file << target->Output() << "\n\n";
        }
        file.close();
        this_thread::sleep_for(chrono::seconds(1));
    }
    fstream file;
    file.open(path, ios::app);
    if (file) {
        file << target->Output();
    }
    file.close();
}
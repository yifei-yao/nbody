#include "engine.h"
#include "solver.h"
#include "string_tool.h"
#include <iostream>
#include <thread>
#include <matplot/matplot.h>

using namespace std;

Engine::Engine() : target(nullptr) {}

bool
Engine::AddObject(const string &name, long double GM,
                  long double X, long double Y, long double Z,
                  long double VX, long double VY, long double VZ) {
    if (target == nullptr) { return false; }
    target->AddObject(name, GM, X, Y, Z, VX, VY, VZ);
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
                 bool plot, const string &log_path, bool verbose) {
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
    thread plot_thread;
    if (plot) {
        plot_thread = thread(&Engine::Plot, this, end);
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
    if (plot) {
        plot_thread.join();
    }
    cout << target->TableString() << "\n";
    return true;
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

void Engine::Plot(long double end) const {
    using namespace matplot;
    vector<vector<long double>> positions(3);
    UpdatePositions(positions);
    auto f = figure(true);
    f->quiet_mode();
    auto ax = gca();
    auto sc = ax->scatter3(positions[0], positions[1], positions[2], "filled");
    while (end > target->get_time()) {
        UpdatePositions(positions);
        ax->scatter3(positions[0], positions[1], positions[2], "filled");
        f->draw();
        this_thread::sleep_for(chrono::milliseconds (200));
    }
}

void Engine::UpdatePositions(vector<vector<long double>> &positions) const {
    positions[0].clear();
    positions[1].clear();
    positions[2].clear();
    for (Body *object: target->get_objects()) {
        Vector position = object->get_position();
        positions[0].push_back(position.get_x());
        positions[1].push_back(position.get_y());
        positions[2].push_back(position.get_z());
    }
}

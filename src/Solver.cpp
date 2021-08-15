#include "Solver.h"
#include "Vector.h"
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

Solver::Solver(System *target) : target(target) {}

System *Solver::get_target() const {
    return target;
}

FixedStepSolver::FixedStepSolver(System *target) : Solver(target) {}

void Euler::Update(long double step) {
    vector<Body *> objects = get_target()->get_objects();
    for (Body *object: objects) {
        Vector vector1;
        for (Body *object2: objects) {
            if (object2 != object) {
                Vector vector2 =
                        object2->get_position() -
                        object->get_position();
                long double sum_of_squares = vector2.SumOfSquares();
                vector2 *= object2->get_GM() /
                           (sum_of_squares * sqrt(sum_of_squares));
                vector1 += vector2;
            }
        }
        vector1 *= step;
        object->AddBuffer(vector1);
    }
    for (Body *object: objects) {
        Vector displacement = object->get_velocity() * step;
        object->add_position(displacement);
        object->add_velocity(object->get_buffer(0));
        object->ClearBuffer();
    }
    get_target()->AddTime(step);
}

Euler::Euler(System *target) : FixedStepSolver(target) {}

void StepScheduler(FixedStepSolver &solver, long double end,
                   long double time_limit) {
    chrono::duration<long double> total_allocated_time(time_limit);
    auto end_time = chrono::steady_clock::now() + total_allocated_time;
    System *target = solver.get_target();
    auto benchmark_start = chrono::steady_clock::now();
    solver.Update(0);
    auto benchmark_end = chrono::steady_clock::now();
    auto estimated_step_time = benchmark_end - benchmark_start;
    auto estimated_step_num =
            (end_time - chrono::steady_clock::now()) / estimated_step_time;
    if (estimated_step_num < 0) { estimated_step_num = 1; }
    auto estimated_step_size = (end - target->get_time()) / estimated_step_num;
    int total_check_num = 100;
    auto current_recheck_step_num = estimated_step_num / total_check_num;
    --total_check_num;
    size_t exe_num = 0;
    auto timestamp = chrono::steady_clock::now();
    while (target->get_time() < end) {
        solver.Update(estimated_step_size);
        if (exe_num >= current_recheck_step_num && total_check_num > 0) {
            auto time_elapsed = chrono::steady_clock::now() - timestamp;
            estimated_step_time = time_elapsed / exe_num;
            auto estimated_step_remained =
                    (end_time - chrono::steady_clock::now()) /
                    estimated_step_time;
            estimated_step_size =
                    (end - target->get_time()) / estimated_step_remained;
            current_recheck_step_num =
                    estimated_step_remained / total_check_num;
            --total_check_num;
            exe_num = 0;
            timestamp = chrono::steady_clock::now();
        }
        ++exe_num;
    }
}

EulerImproved::EulerImproved(System *target) : FixedStepSolver(target) {}

void EulerImproved::Update(long double step) {
    vector<Body *> objects = get_target()->get_objects();
    for (Body *object: objects) {
        Vector vector1;
        for (Body *object2: objects) {
            if (object2 != object) {
                Vector vector2 =
                        object2->get_position() - object->get_position();
                long double sum_of_squares = vector2.SumOfSquares();
                vector2 *= object2->get_GM() /
                           (sum_of_squares * sqrt(sum_of_squares));
                vector1 += vector2;
            }
        }
        object->AddBuffer(vector1);
    }
    for (Body *object: objects) {
        Vector displacement = object->get_velocity() * step +
                              object->get_buffer(0) * (step * step / 2);
        object->add_position(displacement);
        object->add_velocity(object->get_buffer(0) * step);
        object->ClearBuffer();
    }
    get_target()->AddTime(step);
}
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
                Vector vector2 = object2->get_position();
                vector2 -= object->get_position();
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
        Vector displacement = object->get_velocity();
        displacement *= step;
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

    size_t total_exe_num = 0;

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

        ++total_exe_num;

    }

    cout << "total_exe_num " << total_exe_num << "\n";
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

RK4::RK4(System *target) : FixedStepSolver(target) {}

void RK4::Update(long double step) {
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
        object->AddBuffer(vector1); // a1 at index 0
        vector1 *= step / 2;
        vector1 += object->get_velocity();
        object->AddBuffer(vector1);  // v2 at index 1
        Vector vector3 =
                object->get_position() + object->get_velocity() * (step / 2);
        object->AddBuffer(vector3);  // x for a2 at index 2
        Vector vector4 = object->get_position() + vector1 * (step / 2);
        object->AddBuffer(vector4); // x for a3 at index 3
    }
    for (Body *object: objects) {
        Vector vector1;
        Vector vector2;
        for (Body *object2: objects) {
            if (object2 != object) {
                Vector vector3 =
                        object2->get_buffer(2) - object->get_buffer(2);
                Vector vector4 =
                        object2->get_buffer(3) - object->get_buffer(3);
                long double sum_of_squares_1 = vector3.SumOfSquares();
                long double sum_of_squares_2 = vector4.SumOfSquares();
                vector3 *= object2->get_GM() /
                           (sum_of_squares_1 * sqrt(sum_of_squares_1));
                vector4 *= object2->get_GM() /
                           (sum_of_squares_2 * sqrt(sum_of_squares_2));
                vector1 += vector3;
                vector2 += vector4;
            }
        }
        object->AddBuffer(vector1); // a2 at index 4
        vector1 *= step / 2;
        vector1 += object->get_velocity();
        object->AddBuffer(vector1); // v3 at index 5
        object->AddBuffer(vector2); // a3 at index 6
        vector2 *= step;
        vector2 += object->get_velocity();
        object->AddBuffer(vector2); // v4 at index 7
        vector1 *= step;
        vector1 += object->get_position();
        object->AddBuffer(vector1); // x for a4 at index 8
    }
    for (Body *object: objects) {
        Vector vector1; // a4
        for (Body *object2: objects) {
            if (object2 != object) {
                Vector vector2 =
                        object2->get_buffer(8) -
                        object->get_buffer(8);
                long double sum_of_squares = vector2.SumOfSquares();
                vector2 *= object2->get_GM() /
                           (sum_of_squares * sqrt(sum_of_squares));
                vector1 += vector2;
            }
        }
        Vector delta_x = object->get_velocity() + object->get_buffer(1) * 2 +
                         object->get_buffer(5) * 2 + object->get_buffer(7);
        delta_x *= step / 6;
        object->add_position(delta_x);
        Vector delta_v = object->get_buffer(0) + object->get_buffer(4) * 2 +
                         object->get_buffer(6) * 2 + vector1;
        delta_v *= step / 6;
        object->add_velocity(delta_v);
    }
    for (Body *object: objects) { object->ClearBuffer(); }
    get_target()->AddTime(step);
}
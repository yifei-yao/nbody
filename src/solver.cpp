#include "solver.h"
#include <chrono>

using namespace std;

Solver::Solver(System *target) : target(target) {}

System *Solver::get_target() const {
    return target;
}


void StepScheduler(Solver &solver, long double end,
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

//    size_t total_exe_num = 0;

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

//        ++total_exe_num;
    }
//    cout << "total_exe_num " << total_exe_num << "\n";
}


//
// Created by Yifei Yao on 8/15/21.
//

#ifndef SOLVER_H
#define SOLVER_H

#include "System.h"

class Solver {
public:
    explicit Solver(System *);

    System *get_target() const;

private:
    System *target;
};

class FixedStepSolver : public Solver {
public:
    explicit FixedStepSolver(System *);

    virtual void Update(long double step) = 0;
};

class Euler : public FixedStepSolver {
public:
    explicit Euler(System *);

    void Update(long double) override;
};

void StepScheduler(FixedStepSolver &, long double end,
                   long double time_limit);


#endif //SOLVER_H

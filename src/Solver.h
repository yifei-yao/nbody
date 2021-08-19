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

class EulerImproved : public FixedStepSolver {
public:
    explicit EulerImproved(System *);

    void Update(long double) override;
};

class RK4 : public FixedStepSolver {
public:
    explicit RK4(System *);

    void Update(long double) override;
};

class GeneralRK : public FixedStepSolver {
public:
    explicit GeneralRK(System *, const std::vector<std::vector<long double>> &,
                       const std::vector<long double> &);

    void Update(long double) override;

private:
    static void ScaleTable(std::vector<std::vector<long double>> &table,
                           long double scalar);

    std::vector<std::vector<long double>> inner_table;
    std::vector<long double> b_row;
};


class RK4Example : public GeneralRK {
public:
    explicit RK4Example(System *);
};

class Ralston4 : public GeneralRK {
public:
    explicit Ralston4(System *);
};

void StepScheduler(FixedStepSolver &, long double end, long double time_limit);

#endif //SOLVER_H
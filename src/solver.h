#ifndef SOLVER_H
#define SOLVER_H

#include "system.h"

class Solver {
public:
    explicit Solver(System *);

    [[nodiscard]] System *get_target() const;

    virtual void Update(long double step) = 0;

private:
    System *target;
};

class Euler : public Solver {
public:
    explicit Euler(System *);

    void Update(long double) override;
};

class EulerImproved : public Solver {
public:
    explicit EulerImproved(System *);

    void Update(long double) override;
};

class RK4 : public Solver {
public:
    explicit RK4(System *);

    void Update(long double) override;
};

class RKGeneral : public Solver {
public:
    explicit RKGeneral(System *, const std::vector<std::vector<long double>> &,
                       const std::vector<long double> &);

    void Update(long double) override;

private:
    static void ScaleTable(std::vector<std::vector<long double>> &table,
                           long double scalar);

    std::vector<std::vector<long double>> inner_table;
    std::vector<long double> b_row;
};

class Ralston4 : public RKGeneral {
public:
    explicit Ralston4(System *);
};

void StepScheduler(Solver &, long double end, long double time_limit);

#endif //SOLVER_H
#ifndef ENGINE_H
#define ENGINE_H

#include "system.h"

class Engine {
public:
    Engine();

    ~Engine();

    bool
    AddObject(const std::string &, long double,
              long double, long double, long double,
              long double, long double, long double);

    [[nodiscard]] bool Save(const std::string &) const;

    bool Load(const std::string &);

    bool Run(long double end, long double time_limit,
             const std::string &method, bool plot,
             const std::string &log_path = std::string(),
             bool verbose = false);

private:
    void Plot(long double end) const;

    void UpdatePositions(std::vector<std::vector<long double>> &positions) const;

    void PrintProgressBar(long double end) const;

    void RealtimePrint(long double end) const;

    void Log(long double end, const std::string &) const;

    System *target;
};

#endif //ENGINE_H
#ifndef ENGINE_H
#define ENGINE_H

#include "System.h"

class Engine {
public:
    Engine();

    ~Engine();

    void AddTarget(const std::string &, long double = 0);

    bool
    AddObject(const std::string &, long double,
              long double, long double, long double,
              long double, long double, long double);

    bool PrintTarget() const;

    bool Save(const std::string &);

    bool Load(const std::string &);

    bool Run(long double end, long double time_limit,
             const std::string &method = std::string(),
             const std::string &log_path = std::string(),
             bool verbose = false);

private:
    System *target;
};

#endif //ENGINE_H
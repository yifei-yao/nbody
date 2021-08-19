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
             const std::string &method,
             const std::string &log_path = std::string(),
             bool verbose = false);

    bool
    Translate(const std::string &from, long double = 0, long double = 0,
              long double = 0, long double = 0, long double = 0,
              long double= 0);

private:
    void DoTranslation(const Vector &, const Vector &, const Vector &,
                       const Vector &);

    void CalculateBarycenter(Vector &, Vector &);

    void PrintProgressBar(long double end) const;

    System *target;
};

#endif //ENGINE_H
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

    bool Save(const std::string &) const;

    bool Load(const std::string &);

    bool Run(long double end, long double time_limit,
             const std::string &method, bool plot,
             const std::string &log_path = std::string(),
             bool verbose = false);

    bool
    Translate(const std::string &from, long double = 0, long double = 0,
              long double = 0, long double = 0, long double = 0,
              long double= 0);

private:
    void Plot(long double end) const;

    void UpdatePositions(std::vector<std::vector<long double>> &positions) const;

    void DoTranslation(const Vector &, const Vector &, const Vector &,
                       const Vector &);

    void CalculateBarycenter(Vector &, Vector &);

    void PrintProgressBar(long double end) const;

    void RealtimePrint(long double end) const;

    void Log(long double end, const std::string &) const;

    System *target;
};

#endif //ENGINE_H
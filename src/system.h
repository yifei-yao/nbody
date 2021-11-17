#ifndef SYSTEM_H
#define SYSTEM_H

#include "body.h"
#include <vector>

class System {

public:
  explicit System(std::string name, long double time);

  ~System();

  void
  AddObject(const std::string &object_name, long double,
            long double, long double, long double,
            long double, long double, long double);

  void AddTime(long double);

  [[nodiscard]] long double get_time() const;

  [[nodiscard]] std::string TableString() const;

  [[nodiscard]] std::string Output() const;

  const std::vector<Body *> &get_objects();

private:
  std::string name;
  long double time;
  std::vector<Body *> objects;
};

#endif //SYSTEM_H
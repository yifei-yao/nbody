#ifndef BODY_H
#define BODY_H

#include "triplet.h"
#include <string>
#include <iostream>
#include <vector>


class Body {
public:
  Body(std::string name, long double,
       long double, long double, long double,
       long double, long double, long double);

  [[nodiscard]] std::string Output() const;

  [[nodiscard]] std::string TableString() const;

  [[nodiscard]] const Triplet &get_position() const;

  [[nodiscard]] const Triplet &get_velocity() const;

  void add_position(const Triplet &);

  void add_velocity(const Triplet &);

  [[nodiscard]] long double get_GM() const;

  void AddBuffer(const Triplet &);

  [[nodiscard]] const Triplet &get_buffer(int) const;

  void ClearBuffer();

  [[nodiscard]] const Triplet &get_buf_x_last() const;

  [[nodiscard]] const Triplet &get_buf_v(size_t) const;

  [[nodiscard]] const Triplet &get_buf_a(size_t) const;

private:
  std::string name;
  long double GM; //Gravitational parameter (gravitational constant * mass)
  Triplet position;
  Triplet velocity;
  std::vector<Triplet> buffer;
};

#endif //BODY_H
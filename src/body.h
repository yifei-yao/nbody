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

  [[nodiscard]] const Triplet &GetPosition() const;

  [[nodiscard]] const Triplet &GetVelocity() const;

  void AddPosition(const Triplet &);

  void AddVelocity(const Triplet &);

  [[nodiscard]] long double GetGM() const;

  void AddBuffer(const Triplet &);

  [[nodiscard]] const Triplet &GetBuffer(int) const;

  void ClearBuffer();

  [[nodiscard]] const Triplet &GetBufXLast() const;

  [[nodiscard]] const Triplet &GetBufV(size_t) const;

  [[nodiscard]] const Triplet &GetBufA(size_t) const;

private:
  std::string name;
  long double GM; //Gravitational parameter (gravitational constant * mass)
  Triplet position;
  Triplet velocity;
  std::vector<Triplet> buffer;
};

#endif //BODY_H
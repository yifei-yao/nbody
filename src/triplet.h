#ifndef TRIPLET_H
#define TRIPLET_H

#include <ostream>

class Triplet {
  friend Triplet operator-(const Triplet &lhs, const Triplet &rhs);

  friend Triplet operator+(const Triplet &lhs, const Triplet &rhs);

  friend Triplet operator*(const Triplet &lhs, long double scalar);

public:
  explicit Triplet(long double x = 0, long double y = 0, long double z = 0);

  void operator+=(const Triplet &);

  void operator-=(const Triplet &);

  void operator*=(long double scalar);

  void operator/=(long double scalar);

  [[nodiscard]] long double GetX() const;

  [[nodiscard]] long double GetY() const;

  [[nodiscard]] long double GetZ() const;

  [[nodiscard]] std::string Output() const;

  [[nodiscard]] long double SumOfSquares() const;

private:
  long double x;
  long double y;
  long double z;
};

#endif //TRIPLET_H
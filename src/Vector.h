#ifndef VECTOR_H
#define VECTOR_H

#include "ostream"

class Vector {
    friend Vector operator-(const Vector &lhs, const Vector &rhs);

    friend Vector operator+(const Vector &lhs, const Vector &rhs);

    friend Vector operator*(const Vector &lhs, long double scalar);

public:
    explicit Vector(long double x = 0, long double y = 0, long double z = 0);

    void operator+=(const Vector &);

    void operator-=(const Vector &);

    void operator*=(long double scalar);

    long double get_x() const;

    long double get_y() const;

    long double get_z() const;

    std::string Output() const;

    long double SumOfSquares() const;

private:
    long double x;
    long double y;
    long double z;
};

#endif //VECTOR_H
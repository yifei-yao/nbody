#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>

class Vector {
    friend Vector operator-(const Vector &lhs, const Vector &rhs);

    friend Vector operator+(const Vector &lhs, const Vector &rhs);

    friend Vector operator*(const Vector &lhs, long double scalar);

public:
    explicit Vector(long double x = 0, long double y = 0, long double z = 0);

    void operator+=(const Vector &);

    void operator-=(const Vector &);

    void operator*=(long double scalar);

    void operator/=(long double scalar);

    [[nodiscard]] long double get_x() const;

    [[nodiscard]] long double get_y() const;

    [[nodiscard]] long double get_z() const;

    [[nodiscard]] std::string Output() const;

    [[nodiscard]] long double SumOfSquares() const;

private:
    long double x;
    long double y;
    long double z;
};

#endif //VECTOR_H
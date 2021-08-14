//
// Created by Yifei Yao on 8/14/21.
//

#ifndef TRIPLET_H
#define TRIPLET_H

#include "ostream"

class Triplet {
public:
    explicit Triplet(long double x = 0, long double y = 0, long double z = 0);

    long double get_x() const;

    long double get_y() const;

    long double get_z() const;

    std::string Output() const;

private:
    long double x;
    long double y;
    long double z;
};


#endif //TRIPLET_H

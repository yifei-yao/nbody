//
// Created by Yifei Yao on 8/14/21.
//

#include "Body.h"

#include <utility>

using namespace std;

Body::Body(long double GM, Triplet position, Triplet velocity, string name)
        : GM(GM), position(position), velocity(velocity),
          name(std::move(name)) {}

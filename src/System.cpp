//
// Created by Yifei Yao on 8/14/21.
//

#include "System.h"
#include <utility>

using namespace std;

System::System(long double time, string name) : time(time),
                                                name(std::move(name)) {}

void System::AddObject(Body object) {
    objects.push_back(new Body(std::move(object)));
}

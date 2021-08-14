//
// Created by Yifei Yao on 8/14/21.
//

#include "System.h"

System::System(long double time) : time(time) {}

void System::AddObject(Body object) {
    objects.push_back(new Body(object));
}

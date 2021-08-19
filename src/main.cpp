#include "Engine.h"
#include <chrono>
#include <iostream>

int main() {
    Engine hyperdrive;
    hyperdrive.Load("demo.txt");
    hyperdrive.Run(31622400, 1200, "Ralston4");
//    hyperdrive.Translate("Barycenter");
    hyperdrive.Save("result.txt");
}
#include "Engine.h"
#include <chrono>
#include <iostream>

int main() {
    Engine hyperdrive;
    hyperdrive.Load("demo.txt");
    hyperdrive.Run(31622400, 10, "RK4Example");
//    hyperdrive.Translate("Barycenter");
    hyperdrive.Save("result.txt");
}
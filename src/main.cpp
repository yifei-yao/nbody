#include "Engine.h"
#include <chrono>
#include <iostream>

int main() {
    Engine hyperdrive;
    hyperdrive.Load("demo.txt");
    auto start = std::chrono::steady_clock::now();
    hyperdrive.Run(31622400, 1200, "RK4");
    auto end = std::chrono::steady_clock::now();
    hyperdrive.Save("test.txt");
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start).count();
}
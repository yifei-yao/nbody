#include "engine.h"

int main() {
    Engine hyperdrive;
    hyperdrive.Load("demo.txt");
    hyperdrive.Run(31622400, 10, "RK4", true, "log.txt", false);
    hyperdrive.Save("result.txt");
}
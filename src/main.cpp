#include "Engine.h"

int main() {
    Engine hyperdrive;
    hyperdrive.AddTarget("The_Galaxy", 2475823);
    hyperdrive.AddObject("Tatooine", 1.5944e+15, 4.27461e+19, -1.5801e+19,
                         2.3397e+16, -150000, -432333, -362);
    hyperdrive.PrintTarget();
    hyperdrive.Save("Donuts.txt");
    Engine betadrive;
    betadrive.Load("Donuts.txt");
    betadrive.PrintTarget();
}

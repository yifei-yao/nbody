#include "Engine.h"

int main() {
    Engine hyperdrive;
    hyperdrive.Load("demo.txt");
    hyperdrive.Run(31622400, 10, "Ralston4");
//    hyperdrive.Translate("Barycenter");
    hyperdrive.Save("result.txt");
}
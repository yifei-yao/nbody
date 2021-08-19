//
// Created by Yifei Yao on 8/19/21.
//


#include "Solver.h"

Ralston4::Ralston4(System *target) : RKGeneral(target,
                                               {{0.4},
                                                {0.29697761, 0.15875964},
                                                {0.21810040, -3.05096516, 3.83286476}
                                               },
                                               {0.17476028, -0.55148066,
                                                1.20553560, 0.17118478}) {}
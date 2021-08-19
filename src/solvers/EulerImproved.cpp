#include "Solver.h"
#include <vector>
#include <cmath>


using namespace std;


EulerImproved::EulerImproved(System *target) : Solver(target) {}

void EulerImproved::Update(long double step) {
    vector<Body *> objects = get_target()->get_objects();
    for (Body *object: objects) {
        Vector vector1;
        for (Body *object2: objects) {
            if (object2 != object) {
                Vector vector2 = object2->get_position();
                vector2 -= object->get_position();
                long double sum_of_squares = vector2.SumOfSquares();
                vector2 *= object2->get_GM() /
                           (sum_of_squares * sqrt(sum_of_squares));
                vector1 += vector2;
            }
        }
        object->AddBuffer(vector1);
    }
    for (Body *object: objects) {
        Vector displacement = object->get_velocity();
        displacement *= step;
        Vector factor2 = object->get_buffer(0);
        factor2 *= step;
        object->add_velocity(factor2);
        factor2 *= step / 2;
        displacement += factor2;
        object->add_position(displacement);
        object->ClearBuffer();
    }
    get_target()->AddTime(step);
}

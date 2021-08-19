#include "Solver.h"
#include <vector>
#include <cmath>

using namespace std;


RK4::RK4(System *target) : Solver(target) {}

void RK4::Update(long double step) {
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
        object->AddBuffer(vector1); // a1 at index 0
        vector1 *= step / 2;
        vector1 += object->get_velocity();
        object->AddBuffer(vector1);  // v2 at index 1
        Vector vector3 = object->get_velocity();
        vector3 *= step / 2;
        vector3 += object->get_position();
        object->AddBuffer(vector3);  // x for a2 at index 2
        vector1 *= step / 2;
        vector1 += object->get_position();
        object->AddBuffer(vector1); // x for a3 at index 3
    }
    for (Body *object: objects) {
        Vector vector1;
        Vector vector2;
        for (Body *object2: objects) {
            if (object2 != object) {
                Vector vector3 = object2->get_buffer(2);
                vector3 -= object->get_buffer(2);
                Vector vector4 = object2->get_buffer(3);
                vector4 -= object->get_buffer(3);
                long double sum_of_squares_1 = vector3.SumOfSquares();
                long double sum_of_squares_2 = vector4.SumOfSquares();
                vector3 *= object2->get_GM() /
                           (sum_of_squares_1 * sqrt(sum_of_squares_1));
                vector4 *= object2->get_GM() /
                           (sum_of_squares_2 * sqrt(sum_of_squares_2));
                vector1 += vector3;
                vector2 += vector4;
            }
        }
        object->AddBuffer(vector1); // a2 at index 4
        vector1 *= step / 2;
        vector1 += object->get_velocity();
        object->AddBuffer(vector1); // v3 at index 5
        object->AddBuffer(vector2); // a3 at index 6
        vector2 *= step;
        vector2 += object->get_velocity();
        object->AddBuffer(vector2); // v4 at index 7
        vector1 *= step;
        vector1 += object->get_position();
        object->AddBuffer(vector1); // x for a4 at index 8
    }
    for (Body *object: objects) {
        Vector vector1; // a4
        for (Body *object2: objects) {
            if (object2 != object) {
                Vector vector2 = object2->get_buffer(8);
                vector2 -= object->get_buffer(8);
                long double sum_of_squares = vector2.SumOfSquares();
                vector2 *= object2->get_GM() /
                           (sum_of_squares * sqrt(sum_of_squares));
                vector1 += vector2;
            }
        }
        Vector delta_x = object->get_buffer(1);
        delta_x += object->get_buffer(5);
        delta_x *= 2;
        delta_x += object->get_velocity();
        delta_x += object->get_buffer(7);
        delta_x *= step / 6;
        object->add_position(delta_x);
        Vector delta_v = object->get_buffer(4);
        delta_v += object->get_buffer(6);
        delta_v *= 2;
        delta_v += object->get_buffer(0);
        delta_v += vector1;
        delta_v *= step / 6;
        object->add_velocity(delta_v);
    }
    for (Body *object: objects) { object->ClearBuffer(); }
    get_target()->AddTime(step);
}

#include "solver.h"
#include <vector>
#include <cmath>

using namespace std;


RK4::RK4(System *target) : Solver(target) {}

void RK4::Update(long double step) {
  vector<Body *> objects = get_target()->get_objects();
  for (Body *object: objects) {
    Triplet triplet1;
    for (Body *object2: objects) {
      if (object2 != object) {
        Triplet triplet2 = object2->get_position();
        triplet2 -= object->get_position();
        long double sum_of_squares = triplet2.SumOfSquares();
        triplet2 *= object2->get_GM() /
                    (sum_of_squares * sqrt(sum_of_squares));
        triplet1 += triplet2;
      }
    }
    object->AddBuffer(triplet1); // a1 at index 0
    triplet1 *= step / 2;
    triplet1 += object->get_velocity();
    object->AddBuffer(triplet1);  // v2 at index 1
    Triplet triplet3 = object->get_velocity();
    triplet3 *= step / 2;
    triplet3 += object->get_position();
    object->AddBuffer(triplet3);  // x for a2 at index 2
    triplet1 *= step / 2;
    triplet1 += object->get_position();
    object->AddBuffer(triplet1); // x for a3 at index 3
  }
  for (Body *object: objects) {
    Triplet triplet1;
    Triplet triplet2;
    for (Body *object2: objects) {
      if (object2 != object) {
        Triplet triplet3 = object2->get_buffer(2);
        triplet3 -= object->get_buffer(2);
        Triplet triplet4 = object2->get_buffer(3);
        triplet4 -= object->get_buffer(3);
        long double sum_of_squares_1 = triplet3.SumOfSquares();
        long double sum_of_squares_2 = triplet4.SumOfSquares();
        triplet3 *= object2->get_GM() /
                    (sum_of_squares_1 * sqrt(sum_of_squares_1));
        triplet4 *= object2->get_GM() /
                    (sum_of_squares_2 * sqrt(sum_of_squares_2));
        triplet1 += triplet3;
        triplet2 += triplet4;
      }
    }
    object->AddBuffer(triplet1); // a2 at index 4
    triplet1 *= step / 2;
    triplet1 += object->get_velocity();
    object->AddBuffer(triplet1); // v3 at index 5
    object->AddBuffer(triplet2); // a3 at index 6
    triplet2 *= step;
    triplet2 += object->get_velocity();
    object->AddBuffer(triplet2); // v4 at index 7
    triplet1 *= step;
    triplet1 += object->get_position();
    object->AddBuffer(triplet1); // x for a4 at index 8
  }
  for (Body *object: objects) {
    Triplet triplet1; // a4
    for (Body *object2: objects) {
      if (object2 != object) {
        Triplet triplet2 = object2->get_buffer(8);
        triplet2 -= object->get_buffer(8);
        long double sum_of_squares = triplet2.SumOfSquares();
        triplet2 *= object2->get_GM() /
                    (sum_of_squares * sqrt(sum_of_squares));
        triplet1 += triplet2;
      }
    }
    Triplet delta_x = object->get_buffer(1);
    delta_x += object->get_buffer(5);
    delta_x *= 2;
    delta_x += object->get_velocity();
    delta_x += object->get_buffer(7);
    delta_x *= step / 6;
    object->add_position(delta_x);
    Triplet delta_v = object->get_buffer(4);
    delta_v += object->get_buffer(6);
    delta_v *= 2;
    delta_v += object->get_buffer(0);
    delta_v += triplet1;
    delta_v *= step / 6;
    object->add_velocity(delta_v);
  }
  for (Body *object: objects) { object->ClearBuffer(); }
  get_target()->AddTime(step);
}

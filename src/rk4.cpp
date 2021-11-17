#include "solver.h"
#include <vector>
#include <cmath>

using namespace std;


RK4::RK4(System *target) : Solver(target) {}

void RK4::Update(long double step) {
  vector<Body *> objects = get_target()->GetObjects();
  for (Body *object: objects) {
    Triplet triplet1;
    for (Body *object2: objects) {
      if (object2 != object) {
        Triplet triplet2 = object2->GetPosition();
        triplet2 -= object->GetPosition();
        long double sum_of_squares = triplet2.SumOfSquares();
        triplet2 *= object2->GetGM() /
                    (sum_of_squares * sqrt(sum_of_squares));
        triplet1 += triplet2;
      }
    }
    object->AddBuffer(triplet1); // a1 at index 0
    triplet1 *= step / 2;
    triplet1 += object->GetVelocity();
    object->AddBuffer(triplet1);  // v2 at index 1
    Triplet triplet3 = object->GetVelocity();
    triplet3 *= step / 2;
    triplet3 += object->GetPosition();
    object->AddBuffer(triplet3);  // x for a2 at index 2
    triplet1 *= step / 2;
    triplet1 += object->GetPosition();
    object->AddBuffer(triplet1); // x for a3 at index 3
  }
  for (Body *object: objects) {
    Triplet triplet1;
    Triplet triplet2;
    for (Body *object2: objects) {
      if (object2 != object) {
        Triplet triplet3 = object2->GetBuffer(2);
        triplet3 -= object->GetBuffer(2);
        Triplet triplet4 = object2->GetBuffer(3);
        triplet4 -= object->GetBuffer(3);
        long double sum_of_squares_1 = triplet3.SumOfSquares();
        long double sum_of_squares_2 = triplet4.SumOfSquares();
        triplet3 *= object2->GetGM() /
                    (sum_of_squares_1 * sqrt(sum_of_squares_1));
        triplet4 *= object2->GetGM() /
                    (sum_of_squares_2 * sqrt(sum_of_squares_2));
        triplet1 += triplet3;
        triplet2 += triplet4;
      }
    }
    object->AddBuffer(triplet1); // a2 at index 4
    triplet1 *= step / 2;
    triplet1 += object->GetVelocity();
    object->AddBuffer(triplet1); // v3 at index 5
    object->AddBuffer(triplet2); // a3 at index 6
    triplet2 *= step;
    triplet2 += object->GetVelocity();
    object->AddBuffer(triplet2); // v4 at index 7
    triplet1 *= step;
    triplet1 += object->GetPosition();
    object->AddBuffer(triplet1); // x for a4 at index 8
  }
  for (Body *object: objects) {
    Triplet triplet1; // a4
    for (Body *object2: objects) {
      if (object2 != object) {
        Triplet triplet2 = object2->GetBuffer(8);
        triplet2 -= object->GetBuffer(8);
        long double sum_of_squares = triplet2.SumOfSquares();
        triplet2 *= object2->GetGM() /
                    (sum_of_squares * sqrt(sum_of_squares));
        triplet1 += triplet2;
      }
    }
    Triplet delta_x = object->GetBuffer(1);
    delta_x += object->GetBuffer(5);
    delta_x *= 2;
    delta_x += object->GetVelocity();
    delta_x += object->GetBuffer(7);
    delta_x *= step / 6;
    object->AddPosition(delta_x);
    Triplet delta_v = object->GetBuffer(4);
    delta_v += object->GetBuffer(6);
    delta_v *= 2;
    delta_v += object->GetBuffer(0);
    delta_v += triplet1;
    delta_v *= step / 6;
    object->AddVelocity(delta_v);
  }
  for (Body *object: objects) { object->ClearBuffer(); }
  get_target()->AddTime(step);
}

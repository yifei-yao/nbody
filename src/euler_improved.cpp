#include "solver.h"
#include <vector>
#include <cmath>


using namespace std;


EulerImproved::EulerImproved(System *target) : Solver(target) {}

void EulerImproved::Update(long double step) {
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
    object->AddBuffer(triplet1);
  }
  for (Body *object: objects) {
    Triplet displacement = object->GetVelocity();
    displacement *= step;
    Triplet factor2 = object->GetBuffer(0);
    factor2 *= step;
    object->AddVelocity(factor2);
    factor2 *= step / 2;
    displacement += factor2;
    object->AddPosition(displacement);
    object->ClearBuffer();
  }
  get_target()->AddTime(step);
}

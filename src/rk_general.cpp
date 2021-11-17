#include "solver.h"
#include <vector>
#include <cmath>

using namespace std;

RKGeneral::RKGeneral(System *target, const vector<vector<long double>> &table,
                     const vector<long double> &row) : Solver(target),
                                                       inner_table(table),
                                                       b_row(row) {}


void RKGeneral::Update(long double step) {
  vector<vector<long double>> ref_table = inner_table;
  ScaleTable(ref_table, step);
  vector<Body *> objects = get_target()->GetObjects();
  for (Body *object: objects) {
    object->AddBuffer(object->GetVelocity());
    object->AddBuffer(object->GetPosition());
  }
  for (auto &row: ref_table) {
    for (Body *object1: objects) {
      Triplet acceleration;
      for (Body *object2: objects) {
        if (object2 != object1) {
          Triplet factor = object2->GetBufXLast();
          factor -= object1->GetBufXLast();
          long double sum_of_squares = factor.SumOfSquares();
          factor *= object2->GetGM() /
                    (sum_of_squares * sqrt(sum_of_squares));
          acceleration += factor;
        }
      }
      object1->AddBuffer(acceleration);
      Triplet velocity = object1->GetVelocity();
      Triplet position = object1->GetPosition();
      for (int i = 0; i < row.size(); ++i) {
        velocity += object1->GetBufA(i) * row[i];
        position += object1->GetBufV(i) * row[i];
      }
      object1->AddBuffer(velocity);
      object1->AddBuffer(position);
    }
  }
  for (Body *object1: objects) {
    Triplet acceleration;
    for (Body *object2: objects) {
      if (object2 != object1) {
        Triplet factor = object2->GetBufXLast();
        factor -= object1->GetBufXLast();
        long double sum_of_squares = factor.SumOfSquares();
        factor *= object2->GetGM() /
                  (sum_of_squares * sqrt(sum_of_squares));
        acceleration += factor;
      }
    }
    object1->AddBuffer(acceleration);
  }
  for (Body *object: objects) {
    Triplet delta_x;
    Triplet delta_v;
    for (int i = 0; i < b_row.size(); ++i) {
      delta_v += object->GetBufA(i) * b_row[i];
      delta_x += object->GetBufV(i) * b_row[i];
    }
    delta_x *= step;
    delta_v *= step;
    object->AddPosition(delta_x);
    object->AddVelocity(delta_v);
    object->ClearBuffer();
  }
  get_target()->AddTime(step);
}

void
RKGeneral::ScaleTable(vector<vector<long double>> &table, long double scalar) {
  for (vector<long double> &vec: table) {
    for (long double &num: vec) {
      num *= scalar;
    }
  }
}
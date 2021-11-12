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
    vector<Body *> objects = get_target()->get_objects();
    for (Body *object: objects) {
        object->AddBuffer(object->get_velocity());
        object->AddBuffer(object->get_position());
    }
    for (auto &row : ref_table) {
        for (Body *object1: objects) {
            Vector acceleration;
            for (Body *object2: objects) {
                if (object2 != object1) {
                    Vector factor = object2->get_buf_x_last();
                    factor -= object1->get_buf_x_last();
                    long double sum_of_squares = factor.SumOfSquares();
                    factor *= object2->get_GM() /
                              (sum_of_squares * sqrt(sum_of_squares));
                    acceleration += factor;
                }
            }
            object1->AddBuffer(acceleration);
            Vector velocity = object1->get_velocity();
            Vector position = object1->get_position();
            for (int i = 0; i < row.size(); ++i) {
                velocity += object1->get_buf_a(i) * row[i];
                position += object1->get_buf_v(i) * row[i];
            }
            object1->AddBuffer(velocity);
            object1->AddBuffer(position);
        }
    }
    for (Body *object1: objects) {
        Vector acceleration;
        for (Body *object2: objects) {
            if (object2 != object1) {
                Vector factor = object2->get_buf_x_last();
                factor -= object1->get_buf_x_last();
                long double sum_of_squares = factor.SumOfSquares();
                factor *= object2->get_GM() /
                          (sum_of_squares * sqrt(sum_of_squares));
                acceleration += factor;
            }
        }
        object1->AddBuffer(acceleration);
    }
    for (Body *object: objects) {
        Vector delta_x;
        Vector delta_v;
        for (int i = 0; i < b_row.size(); ++i) {
            delta_v += object->get_buf_a(i) * b_row[i];
            delta_x += object->get_buf_v(i) * b_row[i];
        }
        delta_x *= step;
        delta_v *= step;
        object->add_position(delta_x);
        object->add_velocity(delta_v);
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
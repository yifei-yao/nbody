//
// Created by Yifei Yao on 8/14/21.
//

#include "StringTool.h"
#include <sstream>
#include <iomanip>

using namespace std;

namespace string_tool {
    string PreciseOut(long double number) {
        stringstream ss;
        ss << fixed << showpoint;
        ss << setprecision(std::numeric_limits<long double>::digits10);
        ss << number;
        return ss.str();
    }
}
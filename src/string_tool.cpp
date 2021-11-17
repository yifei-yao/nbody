#include "string_tool.h"
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

  string PercentageOut(long double number) {
    stringstream ss, ss2;
    ss << number * 100;
    return ss.str().substr(0, 4);
  }
}
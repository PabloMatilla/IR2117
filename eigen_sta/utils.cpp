#include <iostream>
#include "utils.hpp"

using Eigen::VectorXd;

std::istream& operator>>(std::istream& in, VectorXd& v)  {
    double element;
    int i = 0;
    while (not in.eof()) {
        v.resize(i+1);
        v(i++) = element;
        in >> element;
    }
    return in;
}

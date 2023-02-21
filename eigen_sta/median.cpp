#include <iostream>
#include "utils.hpp"
#include <Eigen/Dense>

using Eigen::VectorXd;
int main() {
    double m;
    VectorXd elements = LeerElementosV();
    int n = elements.size();

    if (n % 2 == 0) {
        m = double(elements[n/2 -1] + elements[n/2])/2;
    } else {
        m  = elements[n/2];
    }
    std::cout << "Median: " << m << std::endl;
    return 0;
}


#include <iostream>
#include <Eigen/Dense>
#include "utils.hpp"

using Eigen::VectorXd;
int main() {
    double m;
    VectorXd elements = LeerElementosV();

    std::cout << "Mode: " << m << std::endl;
    return 0;
}


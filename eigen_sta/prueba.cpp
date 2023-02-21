#include "utils.hpp"
#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main() {
    MatrixXd m = LeerElementosM();
    std::cout << m << std::endl;

    VectorXd v = LeerElementosV();
    std::cout << v << std::endl;

    return 0;
}

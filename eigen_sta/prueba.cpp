#include "utils.hpp"
#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main() {
    MatrixXd m = LeerElementos();
    std::cout << m << std::endl;
    return 0;
}

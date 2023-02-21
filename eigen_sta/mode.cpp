#include <iostream>
#include "utils.hpp"
#include <Eigen/Dense>

using Eigen::VectorXd;
int main() {
    VectorXd v = LeerElementosV();
    std::cout << "La media es: " << v.mean() << std::endl;
    return 0;
}


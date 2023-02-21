#include <iostream>
#include "utils.hpp"
#include <Eigen/Dense>

using Eigen::VectorXd;
int main() {
    double m;
    VectorXd elements = LeerElementosV();
    int n = elements.size();


    std::cout << "Median: " << m << std::endl;
    return 0;
}


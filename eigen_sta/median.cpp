#include <iostream>
#include "utils.hpp"
#include <Eigen/Dense>

using Eigen::VectorXd;
int main() {
    double m;
    VectorXd elements;
    std::cin >> elements;
    std::sort(elements.data(), elements.data() + elements.size());
    int n = elements.size();

    if (n % 2) {
        m = double(elements[(n)/2 ] + elements[n/2+1])/2;
    } else {
        m  = elements[n/2];
    }
    std::cout << "Median: " << m << std::endl;
    return 0;
}


#include <iostream>
#include "utils.hpp"

using Eigen::MatrixXd;
using Eigen::VectorXd;

MatrixXd LeerElementos() {
    int n;
    double sumamax = 0;
    std::cout << "Introduzca el tamano de la matrix";
    std::cin >> n;

    MatrixXd m(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double element;
            std::cout << "Introduce el elemento ("<< i << "," << j << "): ";
            std::cin >> element;
            m(i, j) = element;
        }
    }
    return m;
}

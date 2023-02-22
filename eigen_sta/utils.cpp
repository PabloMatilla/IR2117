#include <iostream>
#include "utils.hpp"

using Eigen::MatrixXd;
using Eigen::VectorXd;

MatrixXd LeerElementosM() {
    int n;
    std::cout << "Introduzca el tamano de la matrix (cuadrada): ";
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

VectorXd LeerElementosV() {
    int n ;
    std::cout << "Introduzca el tamano del vector (siempre podra ser menor): ";
    std::cin >> n;

    double element;
    VectorXd m(n);

    int i = 0;
    while (i < n and not std::cin.eof()) {
        std::cin >> element;
        m[i] = element;
        i++;
    }

     /*
    for (int i = 0; i < n; i++) {
            double element;
            std::cout << "Introduce el elemento ("<< i << "): ";
            std::cin >> element;
            m(i) = element;
    } */

    return m.segment(0,i);
}

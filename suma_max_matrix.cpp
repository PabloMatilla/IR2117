#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main () {
    int n;
    double sumamax = 0;
    std::cout << "Introduce el tamano de la matrix: ";
    std::cin >> n;

    MatrixXd m(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double element;
            std::cout << "Introduce el elemento ("<< i << "," << j << ")" << std::endl;
            std::cin >> element;
            m(i, j) = element;
        }
    }
    std::cout << "La matriz es: " << std::endl << m << std::endl;
    std::cout << "La suma mayor es: " << sumamax << std::endl;
    double s = m.row(0).sum();
    std::cout << "The sum of row 0 is " << s << std::endl;
}

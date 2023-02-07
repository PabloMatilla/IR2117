#include <iostream>
#include <cmath>
#include <complex>

int main() {
    std::cout << "Programa para buscar la solucion de una ecuacion cuadrada ax^2 + bx + c = 0" << std::endl;
    double a, b, c, disc, sol1, sol2;
    std::cout << "Introduce el valor de a: ";
    std::cin >> a;
    std::cout << "Introduce el valor de b: ";
    std::cin >> b;
    std::cout << "Introduce el valor de c: ";
    std::cin >> c;

    disc = pow(b, 2) - 4 * a * c;

    if (disc > 0) {
        sol1 = -b + (pow(disc, 1/2)) / (2*a);
        sol2 = -b - (pow(disc, 1/2)) / (2*a);
        std::cout << "La solucion es x1 = " << sol1 << std::endl;
        std::cout << "La solucion es x2 = " << sol2 << std::endl;
    }
    else if (disc == 0){
        sol1 = -b / (2*a);
        std::cout << "La solucion es x1 = " << sol1 << std::endl;
    }
    else{
        std::complex<double> raiz_disc = sqrt(std::complex<double>(disc));
        std::complex<double> sol1 = -b + raiz_disc / (2*a);
        std::complex<double> sol2 = -b - raiz_disc / (2*a);
        std::cout << "La solucion es x1 = " << sol1 << std::endl;
        std::cout << "La solucion es x2 = " << sol2 << std::endl;
    }
    return 0;

}

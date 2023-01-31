#include <iostream>
int main() {
    int a = 0, b = 0, suma = 0;
    while (a < 1) {
        std::cout << "Introduzca el primer valor (a): ";
        std::cin >> a;
    }
    while (b < 1) {
        std::cout << "Introduzca el segundo valor (b): ";
        std::cin >> b;
    }

    for (int i = a; i <= b; i++) {
        suma += i;
    }
    std::cout << "La suma es " << suma << std::endl;
    return 0;
}
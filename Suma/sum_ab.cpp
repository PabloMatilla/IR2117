#include <iostream>

int main() {
    int a, b, suma = 0;
    std::cout << "Introduce el primer valor (a): ";
    std::cin >> a;
    std::cout << "Introduce el segundo valor (b): ";
    std::cin >> b;

    for (int i = a; i <= b; i++) {
        suma += i;
    }
    std::cout << "El valor de la suma es " << suma << std::endl;
    return 0;
}
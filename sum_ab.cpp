#include <iostream>
int main() {
    int a, b, suma = 0;
    std::cout << "Introduzca el primer valor (a): ";
    std::cin >> a;
    std::cout << "Introduzca el segundo valor (b): ";
    std::cin >> b;
    for (int i = a; i <= b; i++) {
        suma += i;
    }
    std::cout << "La suma es " << suma << std::endl;
    return 0;
}
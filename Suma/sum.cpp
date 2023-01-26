#include <iostream>

int sum(int valor);

int main() {
    int n;
    std::cout << "Enter a number: ";
    std::cin >> n;
    if ( n >= 1) {
        std::cout << sum(n) << std::endl;
    }
    else {std::cout << "El valor no es valido" << std::endl;}
    return 0;
}

int sum(int valor) {
    int suma = 0;
    for (int i = 0; i <= valor; i++) {
        suma += i;
    }
    return suma;
}

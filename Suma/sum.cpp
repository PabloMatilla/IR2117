#include <iostream>

int main() {
    int n, suma = 0;
    std::cout << "Enter a number: ";
    std::cin >> n;
    for (int i = 0; i <= n; i++) {
        suma += i;
    }
    std::cout << suma << std::endl;
    return 0;
}

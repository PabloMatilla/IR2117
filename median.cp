#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    double m = 0;
    int element, n = 0;
    std::vector<int> elements;
    std::cin >> element;
    while(!std::cin.eof()) {
        elements.push_back(element);
        n++;
        std::cin >> element;
    }

    std::cout << "Median: " << m << std::endl;
    return 0;
}
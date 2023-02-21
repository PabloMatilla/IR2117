#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.hpp"

int main() {
    double m = 0;
    std::vector<int> elements = ReadElements();
    int n = elements.size();
    std::sort(elements.begin(), elements.end());

    if (n % 2 == 0) {
        m = double(elements[n/2 -1] + elements[n/2])/2;
    } else {
        m = elements[n/2];

    }

    std::cout << "Median: " << m << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include "utils.hpp"

int main() {
   double m = 0, s = 0;
   std::vector<int> elements = ReadElements();
   int n = elements.size();
   for (int i = 0; i < n; i++)
       s += elements[i];
   m = s/n;
   std::cout << "Aritmetric mean: " << m << std::endl;
   return 0;
}

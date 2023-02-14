#include <iostream>
#include <vector>

int main() {
   double m = 0, s = 0;
   int element, n = 0;
   std::vector<int> elements;
   std::cin >> element;
   while(!std::cin.eof()) {
       elements.push_back(element);
       n++;
       std::cin >> element;
   }
   for (int i = 0; i < n; i++)
       s += elements[i];
   m = s/n;
   std::cout << "Aritmetric mean: " << m << std::endl;
   return 0;
}

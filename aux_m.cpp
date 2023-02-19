#include <iostream>
#include <vector>
#include <algorithm>

int main() {
   double m = 0;
   int element, n = 0;
   std::vector<int> elements;
   std::cin >> element;
   while(!std::cin.eof()) {
       elements.push_back(element);
       n++;
       std::cin >> element;
   }
   std::sort(elements.begin(), elements.end());
   if (n % 2 == 0) { // Impar
        m = double(elements[n/2 -1] + elements[n/2])/2;
       std::cout << "Even" << std::endl;
   } else { // Par
        m = elements[n/2];
       std::cout << "Odd" << std::endl;

   }


   std::cout << "Median: " << m << std::endl;
   return 0;
}

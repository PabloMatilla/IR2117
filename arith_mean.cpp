#include <iostream>

int main() {
   double m = 0, s = 0;
   int num, n = 0;
   std::cin >> num;
   while(!std::cin.eof()) {
       s += num;
       n++;
       std::cin >> num;
   }
   m = s/n;
   std::cout << "Aritmetric mean: " << m << std::endl;
   return 0;
}

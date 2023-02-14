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
   int count[n], max;
   for (int j = 0; j < n; j++) {
       count[j] = 0;
        for (int i = 0; i < n; i++)
            if (elements[i] == elements[j])
                count[j]++;
       if (count[j] > count[max])
           max = j;
   }
   m = elements[max];

   std::cout << "Mode: " << m << std::endl;
   return 0;
}

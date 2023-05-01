#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.hpp"

int main() {
   double m = 0;
   std::vector<int> elements = ReadElements();
   int n = elements.size();
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

#include <iostream>
#include <Eigen/Dense>
#include <map>
#include "utils.hpp"

using Eigen::VectorXd;
int main() {
    double m;
    VectorXd elements = LeerElementosV();
    std::map<int, int> dic;

    for(int i = 0; i < elements.size(); i++) {
        dic[elements[i]]++;
    }

    std::cout << "Mode: " << m << std::endl;
    return 0;
}


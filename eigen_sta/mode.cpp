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

    int m_dic = 0;

    for (auto pair : dic) {
        int value = pair.first;
        int count = pair.second;
        if (count > m_dic) {
            m = value;
            m_dic = count;
        }
    }

    std::cout << "Mode: " << m << std::endl;
    return 0;
}


#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <Eigen/Dense>

using Eigen::VectorXd;

std::istream& operator>>(std::istream& in, VectorXd& v);

#endif /* UTILS_HPP */

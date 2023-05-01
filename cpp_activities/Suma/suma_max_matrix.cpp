#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main () {
    int rows, cols;
    std::cout << "Enter matrix size: ";
    std::cin >> rows;
    cols = rows;
    cols = rows;

    MatrixXd m(rows, cols);
    std::cout << "Enter elements (row-wise): " << std::endl;
    for (int i = 0; i < rows; i++)
        for (int j= 0; j < cols; j++)
            std::cin >> m(i,j);
    std::cout << "The matrix is: " << std::endl << m << std::endl;

    VectorXd s(rows);
    for (int i = 0; i < rows; i++)
        s(i) = m.row(i).sum();
    std::cout << "The sum of rows is " << s << std::endl;

    double maxRowSum = s.maxCoeff();
    std::cout << "The maxium sum of rows is " << maxRowSum << std::endl;

    for (int i = 0; i < cols; i++)
        s(i) = m.col(i).sum();
    std::cout << "The sum of columns is " << std::endl << s << std::endl;
    double maxColSum = s.maxCoeff();
    std::cout << "The maximun sum of columns is " << maxColSum << std::endl;
    double maxSum = maxRowSum > maxColSum ? maxRowSum : maxColSum;
    std::cout << "The maximum sum of rows or colums is " << maxSum << std::endl;
    double sumMainDiag = m.diagonal().sum();
    std::cout << "The sum of the main diagonal is " << sumMainDiag << std::endl;
    double sumSecDiag = m.colwise().reverse().diagonal().sum();
    std::cout << "The sum of the secondary diagonal is " << sumSecDiag << std::endl;
    maxSum = maxSum > sumMainDiag ? maxSum : sumMainDiag;
    maxSum = maxSum > sumSecDiag ? maxSum : sumSecDiag;
    std::cout << "The maximum sum is " << maxSum << std::endl;
}

#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

using Dim = std::tuple<int, int>;
using Mat = std::vector<std::vector<double>>;
using vec = std::vector<double>;

template <typename T> void printContainer(const std::vector<T> &vec) {
  std::cout << "--------------\n";
  for (T item : vec) {
    std::cout << item << "\n";
  }
  std::cout << "--------------\n";
}

class Matrix {

public:
  Dim Dimension;
  Mat matrix;
  double rowsize = 0;
  double columnsize = 0;

  Matrix(Mat mat = {}, Dim Dimension = std::make_tuple(2, 2)) {
    this->matrix = mat;
    this->Dimension = Dimension;
    this->rowsize = std::get<0>(Dimension);
    this->columnsize = std::get<1>(Dimension);
    if (mat.size() == 0) {
      for (int i = 0; i < rowsize; i++) {
        matrix.push_back({});

        for (int j = 0; j < columnsize; j++) {
          matrix[i].push_back(0);
        }
      }
    }
  }

  static Matrix dot(Matrix m1, Matrix m2) {
    if (m1.columnsize != m2.rowsize) { // m1.col != m2.rowj
      throw std::invalid_argument(
          "INVALID OPERATION UNEQUAL DIMENSIONS! Matrix of columnsize " +
          std::to_string(m1.columnsize) + " and Matrix of rowsize of " +
          std::to_string(m2.rowsize));
    }

    Matrix matrixProduct({}, std::make_tuple(m1.rowsize, m2.columnsize));

    for (int i = 0; i < m1.columnsize; i++) {
      vec m1_row = m1.getRow(i);
      for (int j = 0; j < m2.columnsize; j++) {
        vec m2_col = m2.getCol(j);

        std::vector<double> elementProduct;
        for (int k = 0; k < m2_col.size(); k++) {

          elementProduct.push_back(m1_row[k] * m2_col[k]);

          if (k == m2_col.size() -
                       1) { // last cycle add all the number to get the product
            double sum_of_elems{};
            for (double x : elementProduct) {
              sum_of_elems += x;
            }
            matrixProduct.matrix[i][j] = sum_of_elems;
          }
        }
      }
    }

    return matrixProduct;
  }
  vec getRow(int n) { return this->matrix[n]; }
  vec getCol(int n) {
    vec res;
    for (int i = 0; i < rowsize; i++) {
      res.push_back(this->matrix[i][n]);
    }
    return res;
  }
  void print() {
    for (int i = 0; i < rowsize; i++) {

      std::cout << "\n";
      std::cout << "(";
      for (int j = 0; j < columnsize; j++) {
        std::cout << matrix[i][j];
        j != columnsize - 1 ? std::cout << "\t" : std::cout << "";
      }
      std::cout << ")";
    }
  }
};

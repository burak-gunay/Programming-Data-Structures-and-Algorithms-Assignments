#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows.resize(numRows);
    for (int i = 0; i < r; i++) {
      rows[i].resize(numColumns);
    }
  }
  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {
    // typename std::vector<std::vector<T> >::iterator lhs = rows.begin();
    // typename std::vector<std::vector<T> >::iterator rrhs = rhs.rows.begin();
    // while (rrhs != rhs.rows.end()) {
    //   rows.push_back(new std::vector<T>);
    //   *lhs = *rrhs;
    //   ++lhs;
    //   ++rrhs;
    //}
  }
  ~Matrix() {
    // for (int i = 0; i < numRows; i++) {
    //   delete rows[i];
    // }
    // delete[] rows;
  }
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      this->rows = rhs.rows;
      this->numRows = rhs.numRows;
      this->numColumns = rhs.numColumns;
    }
    // rows = new std::vector<T> *[rhs.numRows];
    // for (int i = 0; i < rhs.numRows; i++) {
    //   rows[i] = new std::vector<T>;
    //   *rows[i] = *(rhs.rows[i]);
    // }
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index < this->numRows);
    assert(index >= 0);
    // typename std::vector<std::vector<T> >::iterator lhs = rows.begin();
    // while (lhs != rows.end()) {
    //   ++lhs;
    // }
    return this->rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index < this->numRows);
    assert(index >= 0);
    // typename std::vector<std::vector<T> >::iterator lhs = rows.begin();
    // while (lhs != rows.end()) {
    //   ++lhs;
    // }
    return this->rows[index];
  }
  bool operator==(const Matrix & rhs) const {
    if ((numColumns != rhs.numColumns) || (numRows != rhs.numRows) || (rows != rhs.rows)) {
      return false;
    }
    // for (int i = 0; i < numRows; i++) {
    //   if (*rows[i] != *rhs.rows[i]) {
    //     return false;
    //   }
    // }
    return true;
  }
  Matrix operator+(const Matrix & rhs) const {
    assert(this->numRows == rhs.numRows);
    assert(this->numColumns == rhs.numColumns);
    Matrix result(numRows, numColumns);

    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        result.rows[i][j] = this->rows[i][j] + rhs.rows[i][j];
      }
    }
    return result;
  }
};
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  s << "[ {";
  for (int i = 0; i < rhs.getRows(); i++) {
    for (int j = 0; j < rhs.getColumns() - 1; j++) {
      std::cout << rhs[i][j] << ", ";
    }
    if (i == rhs.getRows() - 1) {
      std::cout << rhs[i][rhs.getColumns() - 1] << "} ]";
      break;
    }
    std::cout << rhs[i][rhs.getColumns() - 1] << "}," << std::endl << "{";
  }

  return s;
}
//YOUR CODE GOES HERE!

#endif

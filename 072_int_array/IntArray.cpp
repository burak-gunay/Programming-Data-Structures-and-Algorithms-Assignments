#include "IntArray.h"

#include <assert.h>

#include <iostream>
#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {}

IntArray::IntArray(const IntArray & rhs) :
    //If copied like this, might not delete previous memory ->Ask(will not cause problem)
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < rhs.numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    if (data != NULL) {
      delete[] data;
    }
    data = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      data[i] = rhs.data[i];
    }
    numElements = rhs.numElements;
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index <= (numElements - 1));
  const int & p = data[index];
  return p;
}
int & IntArray::operator[](int index) {
  assert(index <= (numElements - 1));
  int & p = data[index];
  return p;
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  bool result = IntArray::operator==(rhs);
  if (result == true) {
    return false;
  }
  return true;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() == 0) {
    s << "{}";
    return s;
  }
  s << "{";
  for (int i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }
  s << rhs[rhs.size() - 1] << "}";
  return s;
}

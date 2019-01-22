#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
void argc1(std::istream & t) {
  std::string temp;
  std::vector<std::string> vector;
  while (std::getline(t, temp)) {
    vector.push_back(temp);
  }
  std::sort(vector.begin(), vector.end());
  std::vector<std::string>::iterator it = vector.begin();
  while (it != vector.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}
int main(int argc, char ** argv) {
  if (argc == 1) {
    argc1(std::cin);
  }
  for (int i = 1; i < argc; i++) {
    std::ifstream file;
    std::string temp;
    std::vector<std::string> vector;
    file.open(argv[i]);
    if (!file.good() || !file.is_open()) {
      std::cerr << "File not read";
      return EXIT_FAILURE;
    }
    while (std::getline(file, temp)) {
      vector.push_back(temp);
    }
    std::sort(vector.begin(), vector.end());

    std::vector<std::string>::iterator it = vector.begin();
    while (it != vector.end()) {
      std::cout << *it << std::endl;
      ++it;
    }

    file.close();
  }
  return EXIT_SUCCESS;
}

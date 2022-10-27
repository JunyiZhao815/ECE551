#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::string line;
    std::vector<std::string> vector;
    while (!std::cin.eof()) {
      std::getline(std::cin, line);
      vector.push_back(line);
    }
    std::sort(vector.begin(), vector.end());
    std::vector<std::string>::iterator it = vector.begin();
    while (it != vector.end()) {
      std::cout << *it << std::endl;
      ++it;
    }
    vector.clear();
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream file(argv[i]);
      std::vector<std::string> vector;
      std::string line;
      while (!std::cin.eof()) {
        std::getline(file, line);
        vector.push_back(line);
      }
      std::sort(vector.begin(), vector.end());
      std::vector<std::string>::iterator it = vector.begin();
      while (it != vector.end()) {
        std::cout << *it << std::endl;
        ++it;
      }
      vector.clear();
    }
  }
}

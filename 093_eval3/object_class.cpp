#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class line {
 public:
  size_t number;
  size_t index;
  vector<string> text;
  ~line() { text.clear(); }
  size_t getNumber(string line, char target, size_t start) {
    string numStr;
    for (size_t i = start; i < line.length(); i++) {
      if (line[i] == target) {
        break;
      }
      ++index;
      if (line[i] == ' ') {
        continue;
      }
      if (line[i] < 48 || line[i] > 57) {
        cerr << "the page number is incorrect" << endl;
      }
    }
    //if there is no @
    if (index == line.length()) {
      cerr << "Cannot find " << target << endl;
    }
    char * end;
    numStr.append(line, start, index);
    const char * numChar = numStr.c_str();
    size_t ans = (size_t)strtol(numChar, &end, 10);
    //delete numChar;
    return ans;
  }
  void printStory() {
    vector<string>::const_iterator it = text.begin();
    while (it != text.end()) {
      cout << *it << endl;
      ++it;
    }
  }
};

using namespace std;
class line_type1 : public line {
 public:
  // size_t number;

  string type;
  string fileName;
  //vector<string> text;
  // size_t index;
  line_type1(string line) {
    index = 0;
    number = getNumber(line, '@', 0);
    getOthers(line);
  }

  //Obtain the type
  void getOthers(string line) {
    ++index;
    if (index + 2 >= line.length()) {
      cerr << "The line input is not complete" << endl;
    }
    //Cannot find ':'
    if (line[index + 1] != ':') {
      cerr << "Cannot find : between page number and file type" << endl;
    }
    if (line[index] == 'N' || line[index] == 'W' || line[index] == 'L') {
      type = line[index];
      fileName = line.substr(index + 2);
      ifstream f(fileName.c_str());
      //f.open(fileName.c_str());
      if (!f) {
        cerr << "Cannot open file!" << endl;
      }
      //use vector to story content
      string line;
      while (getline(f, line)) {
        text.push_back(line);
      }
      f.close();
      //if the type is N or W
      /*
      if (line[index] == 'W') {
        text.push_back("\n");
        text.push_back("Congratulations! You have won. Hooray!");
      }
      else if (line[index] == 'L') {
        text.push_back("\n");
        text.push_back("Sorry, you have lost. Better luck next time!");
      }
      */
    }
    else {
      std::cerr << "Can not detect the type of page" << std::endl;
    }
  }
};
using namespace std;
class line_type2 : public line {
 public:
  //size_t number;

  size_t destpage;
  //vector<string> text;
  line_type2(string line) {
    index = 0;
    number = getNumber(line, ':', 0);
    ++index;
    destpage = getNumber(line, ':', index);
    text.push_back(line.substr(index + 1));
  }
};

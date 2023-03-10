#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class line {
 public:
  int line_type;
  size_t number;
  size_t index;
  map<string, long int> m;
  vector<string> text;
  vector<pair<pair<long int, string>, pair<size_t, string> > > vec;
  virtual ~line() {
    text.clear();
    vec.clear();
    m.clear();
  }
  // Here we not only get the page number, but also clear some mistakes by calling error
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
        exit(EXIT_FAILURE);
      }
    }

    if (line[index - 1] == ' ') {
      cerr << "The page number has a blank at the tail" << endl;
      exit(EXIT_FAILURE);
    }
    //if there is no @
    if (index == line.length()) {
      cerr << "Cannot find " << target << endl;
      exit(EXIT_FAILURE);
    }
    char * end;
    numStr.append(line, start, index);

    for (size_t i = 0; i < numStr.length(); i++) {
      if (numStr[i] == ' ') {
        if (i >= 1 && numStr[i - 1] != ' ') {
          cerr << "There is a blank between the page number" << endl;
          exit(EXIT_FAILURE);
        }
      }
    }
    const char * numChar = numStr.c_str();
    size_t ans = (size_t)strtol(numChar, &end, 10);

    return ans;
  }
  size_t checkNumber(string numStr) {
    char * end;
    for (size_t i = 0; i < numStr.length(); i++) {
      if (numStr[i] == ' ') {
        if (i >= 1 && numStr[i - 1] != ' ') {
          cerr << "There is a blank between the page number" << endl;
          exit(EXIT_FAILURE);
        }
        continue;
      }
      if (numStr[i] < 48 || numStr[i] > 57) {
        cerr << "Some invalid character you input as number" << endl;
        exit(EXIT_FAILURE);
      }
    }
    const char * numChar = numStr.c_str();
    size_t ans = (size_t)strtol(numChar, &end, 10);
    return ans;
  }
};
//declare the first type: line_type who inherits from line
using namespace std;
class line_type1 : public line {
 public:
  char * path;
  string type;
  string fileName;
  // vector<pair<size_t, string> > vec;
  line_type1(string line, char * path) : path(path) {
    index = 0;
    number = getNumber(line, '@', 0);
    getOthers(line);
  }
  void printStory() {
    vector<string>::const_iterator it = text.begin();
    // cout << "Page " << number << endl;
    //cout << "==========" << endl;
    while (it != text.end()) {
      cout << *it << endl;
      ++it;
    }
    if (type == "N") {
      cout << "\n"
           << "What would you like to do?\n"
           << endl;
    }
    else if (type == "W") {
      cout << "\n";
      cout << "Congratulations! You have won. Hooray!\n";
    }
    else {
      cout << "\n";
      cout << "Sorry, you have lost. Better luck next time!\n";
    }
    vector<pair<pair<long int, string>, pair<size_t, string> > >::iterator p_it =
        vec.begin();
    // Here, vector is used to get the choices and print them out.
    size_t choice_number = 1;
    while (p_it != vec.end()) {
      pair<size_t, string> p = (*p_it).second;
      cout << " " << choice_number << ". " << p.second << "\n";
      ++choice_number;
      ++p_it;
    }
    ++it;
  }

  //Obtain the type
  void getOthers(string line) {
    ++index;
    if (index + 2 >= line.length()) {
      cerr << "The line input is not complete" << endl;
      exit(EXIT_FAILURE);
    }
    //Cannot find ':'
    if (line[index + 1] != ':') {
      cerr << "Cannot find : between page number and file type" << endl;
      exit(EXIT_FAILURE);
    }
    if (line[index] == 'N' || line[index] == 'W' || line[index] == 'L') {
      type = line[index];
      fileName = line.substr(index + 2);
      ostringstream totalPath;
      totalPath << path << "/" << fileName;
      ifstream f(totalPath.str().c_str());

      if (!f) {
        cerr << "Cannot open each story file!" << endl;
        exit(EXIT_FAILURE);
      }
      //use vector to story content
      string line;
      while (getline(f, line)) {
        text.push_back(line);
      }
      f.close();
    }
    else {
      std::cerr << "Can not detect the type of page" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
};

//declare a second type: line_type2 who inherits from line
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

class line_type3 : public line {
 public:
  //number size_t
  string variable;
  long int value;
  line_type3(string line) {
    index = 0;
    number = getNumber(line, '$', 0);
    ++index;
    variable = line.substr(line.find('$') + 1, line.find('=') - line.find('$') - 1);
    string numStr = line.substr(line.find('=') + 1);
    value = (size_t)checkNumber(numStr);
    ;
  }
};
class line_type4 : public line {
 public:
  //number: size_t
  // text: string
  string variable;
  long int value;
  size_t dest;
  line_type4(string line) {
    index = 0;
    number = getNumber(line, '[', 0);
    variable = line.substr(line.find('[') + 1, line.find('=') - line.find('[') - 1);
    string valStr = line.substr(line.find('=') + 1, line.find(']') - line.find('=') - 1);
    value = (long int)checkNumber(valStr);
    size_t secondColonIndex = line.find(':');
    string destStr = line.substr(
        line.find(':') + 1, line.find(':', secondColonIndex + 1) - line.find(':') - 1);
    dest = checkNumber(destStr);
    string t = line.substr(line.find(':', secondColonIndex + 1) + 1);
    text.push_back(t);
  }
};

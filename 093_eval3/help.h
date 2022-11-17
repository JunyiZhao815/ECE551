
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "object_class.cpp"

void readStoryFile(char ** argv, vector<line_type1> * v) {
  ifstream f(argv[1]);
  if (!f) {
    cerr << "Cannot open file!" << endl;
    exit(EXIT_FAILURE);
  }
  //I use vector to store the page, and also use the vector inside the line_type1 object to store choices
  string line;
  size_t count = 0;
  while (getline(f, line)) {
    if (line == "") {
      continue;
    }
    char flag = ' ';
    for (size_t i = 0; i < line.length(); i++) {
      if (line[i] == ':' || line[i] == '@') {
        flag = line[i];
        break;
      }
    }
    // When find the line that declares page
    if (flag == '@') {
      line_type1 story(line);
      if (count != story.number) {
        cerr << "The page number does not follow order" << endl;
        exit(EXIT_FAILURE);
      }
      ++count;
      (*v).push_back(story);
    }
    else {
      line_type2 word(line);
      vector<line_type1>::iterator it = (*v).begin();
      bool haveNum = false;
      while (it != (*v).end()) {
        if (word.number == (*it).number) {
          haveNum = true;
          pair<size_t, string> pair;
          pair.first = word.destpage;
          pair.second = *word.text.begin();
          (*it).vec.push_back(pair);
        }
        ++it;
      }
      if (!haveNum) {
        cerr << "The page number has not been declared" << endl;
        exit(EXIT_FAILURE);
      }
    }
  }
  f.close();
}

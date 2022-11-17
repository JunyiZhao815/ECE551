
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

using namespace std;
int main(int argc, char ** argv) {
  ifstream f(argv[1]);
  if (!f) {
    cerr << "Cannot open file!" << endl;
    exit(EXIT_FAILURE);
  }
  //I use vector to store the page, and also use the vector inside the line_type1 object to store choices
  string line;
  vector<line_type1> v;
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
      v.push_back(story);
    }
    else {
      line_type2 word(line);
      vector<line_type1>::iterator it = v.begin();
      bool haveNum = false;
      while (it != v.end()) {
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
  // Here I have finished getting information from the story.txt file, and then starting with print out
  vector<line_type1>::iterator it = v.begin();
  while (it != v.end()) {
    size_t choice_number = 1;
    line_type1 tmp = *it;
    cout << "Page " << tmp.number << endl;
    cout << "==========" << endl;
    tmp.printStory();

    if (tmp.type == "N") {
      cout << "\n"
           << "What would you like to do?\n"
           << endl;
    }
    else if (tmp.type == "W") {
      cout << "\n";
      cout << "Congratulations! You have won. Hooray!\n";
    }
    else {
      cout << "\n";
      cout << "Sorry, you have lost. Better luck next time!\n";
    }
    vector<pair<size_t, string> >::iterator p_it = tmp.vec.begin();
    // Here, vector is used to get the choices and print them out.
    while (p_it != tmp.vec.end()) {
      pair<size_t, string> p = *p_it;
      cout << " " << choice_number << ". " << p.second << "\n";
      ++choice_number;
      ++p_it;
    }
    ++it;
  }
  v.clear();
}

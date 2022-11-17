#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "object_class.cpp"

using namespace std;
int main(int argc, char ** argv) {
  ifstream f(argv[1]);
  if (!f) {
    cerr << "Cannot open file!" << endl;
  }
  string line;
  size_t choice_number = 1;
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
    if (flag == '@') {
      choice_number = 1;
      line_type1 story(line);
      cout << "Page " << story.number << endl;
      cout << "==========" << endl;
      story.printStory();

      if (story.type == "N") {
        cout << "\n"
             << "What would you like to do?\n"
             << endl;
      }
      else if (story.type == "W") {
        cout << "\n";
        cout << "Congratulations! You have won. Hooray!\n";
      }
      else {
        cout << "\n";
        cout << "Sorry, you have lost. Better luck next time!\n";
      }
    }
    else {
      line_type2 choice(line);
      cout << " " << choice_number << ". " << *choice.text.begin() << "\n";
      ++choice_number;
    }
  }
}

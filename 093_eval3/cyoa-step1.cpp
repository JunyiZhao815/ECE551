
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "help.h"
using namespace std;
int main(int argc, char ** argv) {
  vector<line_type1> dest;
  vector<line_type1> * v = &dest;
  readStoryFile(argv, v);
  // Here I have finished getting information from the story.txt file, and then starting with print out
  cout << "foaskfsa";
  vector<line_type1>::iterator it = (*v).begin();
  while (it != (*v).end()) {
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
  (*v).clear();
}

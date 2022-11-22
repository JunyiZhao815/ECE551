
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
  vector<line_type1>::iterator it = (*v).begin();
  while (it != (*v).end()) {
    cout << "Page " << (*it).number << endl;
    cout << "==========" << endl;
    (*it).printStory();
    ++it;
  }
  (*v).clear();
}

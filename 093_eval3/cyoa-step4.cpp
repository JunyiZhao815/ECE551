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
  vector<line_type1> line_type1_vector;
  vector<line_type1> * v = &line_type1_vector;
  map<string, long int> m;

  readStoryFile(argv, v, &m);
  checkProblem(v);
  //begin the story
  askUser(v);
  /*
  vector<line_type1>::iterator it = line_type1_vector.begin();
  while (it != line_type1_vector.end()) {
    vector<pair<size_t, string> >::iterator inner = (*it).vec.begin();
    cout << "==Page: " << (*it).number << "==" << endl;
    map<string, long int>::iterator inin = (*it).m.begin();
    while (inin != (*it).m.end()) {
      cout << (*inin).first << " : " << (*inin).second << endl;
      ++inin;
    }
    while (inner != (*it).vec.end()) {
      cout << "dest: " << (*inner).first << endl;
      cout << "words: " << (*inner).second << endl;
      cout << "-------------------------------------" << endl;
      ++inner;
    }
    ++it;
    cout << endl;
  }
  */
  line_type1_vector.clear();
}

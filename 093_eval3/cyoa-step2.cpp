
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
  readStoryFile(argv, v);
  checkProblem(v);
  //begin the story
  askUser(v, NULL);

  line_type1_vector.clear();
}

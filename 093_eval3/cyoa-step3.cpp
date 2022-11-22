
#include <algorithm>
#include <cstdio>
#include <cstdlib>
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
  readStoryFile(argv, v, NULL);
  checkProblem(v);
  getWinningPath(v);
  line_type1_vector.clear();
}

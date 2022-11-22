#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "object_class.cpp"

void readStoryFile(char ** argv, vector<line_type1> * v) {
  ostringstream path;
  path << argv[1] << "/story.txt";
  ifstream f(path.str().c_str());
  if (!f) {
    cerr << "Cannot open file!!" << endl;
    exit(EXIT_FAILURE);
  };
  //I use vector to store the page, and also use the vector inside the line_type1 object to store choices
  string line;
  size_t count = 0;
  while (getline(f, line)) {
    if (line == "") {
      continue;
    }
    char flag = ' ';
    for (size_t i = 0; i < line.length(); i++) {
      if (line[i] == ':' || line[i] == '@' || line[i] == '$' || line[i] == '[') {
        flag = line[i];
        break;
      }
    }
    // When find the line that declares page
    if (flag == '@') {
      line_type1 story(line, argv[1]);
      if (count != story.number) {
        cerr << "The page number does not follow order" << endl;
        exit(EXIT_FAILURE);
      }
      ++count;
      (*v).push_back(story);
    }
    else if (flag == ':') {
      line_type2 word(line);
      vector<line_type1>::iterator it = (*v).begin();
      bool haveNum = false;
      while (it != (*v).end()) {
        if (word.number == (*it).number) {
          haveNum = true;
          pair<size_t, string> pair1;
          pair1.first = word.destpage;
          pair1.second = *word.text.begin();
          pair<long int, string> pair2;
          pair2.first = -1;
          pair2.second = "";
          pair<pair<long int, string>, pair<size_t, string> > pair3;
          pair3.first = pair2;
          pair3.second = pair1;

          (*it).vec.push_back(pair3);
        }
        ++it;
      }
      if (!haveNum) {
        cerr << "The page number has not been declared" << endl;
        exit(EXIT_FAILURE);
      }
    }
    else if (flag == '$') {
      line_type3 word(line);
      vector<line_type1>::iterator it = (*v).begin();
      while (it != (*v).end()) {
        if (word.number == (*it).number) {
          (*it).m[word.variable] = word.value;
          break;
        }
        ++it;
      }
    }
    else {
      line_type4 word(line);
      vector<line_type1>::iterator it = (*v).begin();
      while (it != (*v).end()) {
        if (word.number == (*it).number) {
          pair<size_t, string> pair1;
          pair1.second = *word.text.begin();
          pair1.first = word.dest;
          pair<long int, string> pair2;
          pair2.first = word.value;
          pair2.second = word.variable;
          pair<pair<long int, string>, pair<size_t, string> > pair3;
          pair3.first = pair2;
          pair3.second = pair1;
          (*it).vec.push_back(pair3);
          break;
        }
        ++it;
      }
    }
  }
  f.close();
}

void checkProblem(vector<line_type1> * v) {
  //Initialize all element in the destlist to be 0
  vector<size_t> destList((*v).size());
  vector<line_type1>::iterator it = (*v).begin();
  //These two flags here are to check if there is at least one win and lose page
  bool flag_win = false;
  bool flag_lose = false;
  while (it != (*v).end()) {
    if ((*it).type == "W") {
      flag_win = true;
    }
    if ((*it).type == "L") {
      flag_lose = true;
    }
    vector<pair<pair<long int, string>, pair<size_t, string> > > line_type2_vector =
        (*it).vec;
    vector<pair<pair<long int, string>, pair<size_t, string> > >::iterator it_inner =
        line_type2_vector.begin();
    while (it_inner != line_type2_vector.end()) {
      //It the page has the choice that references to itself;
      if ((*it_inner).second.first == (*it).number) {
        ++it_inner;
        continue;
      }
      else {
        // 3a: the choice is not valid
        if ((*it_inner).second.first >= (*v).size()) {
          cerr << "Cannot reach the page in the choice" << endl;
          exit(EXIT_FAILURE);
        }
        destList[(*it_inner).second.first] = destList[(*it_inner).second.first] + 1;
        ++it_inner;
      }
    }
    line_type2_vector.clear();
    ++it;
  }
  //3c: No win or lose page
  if (!(flag_win && flag_lose)) {
    cerr << "There is no Win or Lose page!" << endl;
    exit(EXIT_FAILURE);
  }
  // 3b: If every element in the destList is not 0, that means every page is referenced.
  for (size_t i = 1; i < (*v).size(); i++) {
    if (destList[i] == 0) {
      cerr << "Some pages are not referenced!" << endl;
      exit(EXIT_FAILURE);
    }
    /*
    cerr << i << endl;
    cerr << destList[i] << endl;
    cerr << "-------------------" << endl;
    */
  }
}
void askUser(vector<line_type1> * v, map<string, long int> * m) {
  line_type1 current_page = *(*v).begin();
  current_page.printStory();
  line_type1 tmp = current_page;
  while (current_page.type == "N") {
    size_t input;
    cin >> input;
    bool match = false;
    bool unavaliable = false;
    for (size_t i = 0; i < current_page.vec.size(); i++) {
      if (input == i + 1) {
        if (current_page.vec[i].second.second == "<UNAVAILABLE>") {
          unavaliable = true;
          break;
        }
        current_page = (*v)[current_page.vec[i].second.first];
        match = true;
        break;
      }
    }
    if (!match) {
      if (unavaliable) {
        // if the choice is unavaliable
        cout << "That choice is not available at this time, please try again" << endl;
      }
      else {
        //If input does not fit the choices.
        cout << "That is not a valid choice, please try again" << endl;
      }
    }
    while (!match) {
      size_t another_input;
      cin >> another_input;
      if (current_page.vec[another_input - 1].second.second == "<UNAVAILABLE>") {
        cout << "That choice is not available at this time, please try again" << endl;
        continue;
      }
      for (size_t i = 0; i < current_page.vec.size(); i++) {
        if (another_input == i + 1) {
          match = true;
          current_page = (*v)[current_page.vec[i].second.first];
          break;
        }
      }
      cout << "That is not a valid choice, please try again" << endl;
    }
    if (m != NULL) {
      map<string, long int>::iterator it = tmp.m.begin();
      //update what we have.
      while (it != tmp.m.end()) {
        (*m)[(*it).first] = (*it).second;
        ++it;
      }
      vector<pair<pair<long int, string>, pair<size_t, string> > >::iterator it2 =
          current_page.vec.begin();
      while (it2 != current_page.vec.end()) {
        //if is type2
        if ((*it2).first.second == "") {
          ++it2;
          continue;
        }
        //if is type4
        else {
          map<string, long int>::iterator it3 = (*m).begin();
          while (it3 != (*m).end()) {
            if ((*it3).first == (*it2).first.second) {
              if ((*it3).second != (*it2).first.first) {
                (*it2).second.second = "<UNAVAILABLE>";
              }
              break;
            }
            ++it3;
          }
          // If we did not find the variable we have
          if (it3 == (*m).end()) {
            if ((*it2).first.first > 0) {
              (*it2).second.second = "<UNAVAILABLE>";
            }
          }
        }
        ++it2;
      }
    }
    tmp = current_page;
    current_page.printStory();

    // exit(EXIT_SUCCESS);
  }
}
string size_tTostring(size_t num) {
  ostringstream s;
  s << num;
  return s.str();
}
void getPath(vector<line_type1> * v, size_t index, string path, set<size_t> * visited) {
  // When it comes to Win page
  if ((*v)[index].type == "W") {
    string winPage = size_tTostring((*v)[index].number);
    path = path + winPage + "(win)";
    cout << path << endl;
    return;
  }
  // When it comes to Lose page
  if ((*v)[index].type == "L") {
    return;
  }
  // Check if we can go one of the choice
  for (size_t i = 0; i < (*v)[index].vec.size(); i++) {
    if ((*visited).find((*v)[index].vec[i].second.first) != (*visited).end()) {
      continue;
    }
    else {
      string tmp = path;
      path = path + size_tTostring((*v)[index].number);
      (*visited).insert((*v)[index].vec[i].second.first);
      path = path + "(" + size_tTostring(1 + i) + "),";
      getPath(v, (*v)[index].vec[i].second.first, path, visited);
      path = tmp;
      (*visited).erase((*v)[index].vec[i].second.first);
    }
  }
}

void getWinningPath(vector<line_type1> * v) {
  set<size_t> s;
  // visited pointer here points to a set which record if the element has been visited
  set<size_t> * visited = &s;
  if ((*v).size() == 0) {
    return;
  }
  // Using recursion to print the answer.
  getPath(v, 0, "", visited);
  s.clear();
}

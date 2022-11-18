
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
      line_type1 story(line, argv[1]);
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
    vector<pair<size_t, string> > line_type2_vector = (*it).vec;
    vector<pair<size_t, string> >::iterator it_inner = line_type2_vector.begin();
    while (it_inner != line_type2_vector.end()) {
      //It the page has the choice that references to itself;
      if ((*it_inner).first == (*it).number) {
        ++it_inner;
        continue;
      }
      else {
        // 3a: the choice is not valid
        if ((*it_inner).first >= (*v).size()) {
          cerr << "Cannot reach the page in the choice" << endl;
          exit(EXIT_FAILURE);
        }
        destList[(*it_inner).first] = destList[(*it_inner).first] + 1;
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
void askUser(vector<line_type1> * v) {
  line_type1 current_page = *(*v).begin();
  current_page.printStory();
  while (current_page.type == "N") {
    size_t input;
    cin >> input;
    bool match = false;

    for (size_t i = 0; i < current_page.vec.size(); i++) {
      if (input == i + 1) {
        current_page = (*v)[current_page.vec[i].first];
        match = true;
        break;
      }
    }
    while (!match) {
      //If input does not fit the choices.
      cerr << "That is not a valid choice, please try again" << endl;
      size_t another_input;
      cin >> another_input;
      for (size_t i = 0; i < current_page.vec.size(); i++) {
        if (another_input == i + 1) {
          match = true;
          current_page = (*v)[current_page.vec[i].first];
          break;
        }
      }
    }
    current_page.printStory();
  }
  // exit(EXIT_SUCCESS);
}

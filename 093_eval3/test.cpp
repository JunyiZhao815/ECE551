
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
int main() {
  line_type4 t("666668[pastry=11111]:12352:Offer the dragon the chocolate croissant.");
  cout << t.number << endl;
  cout << t.variable << endl;
  cout << t.value << endl;
  cout << t.dest << endl;
  cout << *(t.text.begin()) << endl;

  line_type3 a("12324$pastry=99999");
  cout << a.number << endl;
  cout << a.variable << endl;
  cout << a.value << endl;
}

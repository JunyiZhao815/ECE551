#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!

  uint64_t * arr_pointer = new uint64_t[257]();
  ifstream f(fname);
  if (!f) {
    cerr << "file cannot be opened!!!" << endl;
  }
  char c;
  while (f.get(c)) {
    if ((unsigned char)c >= 0 && (unsigned char)c <= 255) {
      ++arr_pointer[(unsigned char)c];
    }
  }
  arr_pointer[256] = 1;
  f.close();
  return arr_pointer;
}

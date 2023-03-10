#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "fstream"
#include "node.h"
#include "readFreq.h"

using namespace std;
void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  ifstream inF(inFile);
  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  char c;
  while (inF.get(c)) {
    map<unsigned, BitString>::const_iterator it = theMap.find((unsigned char)c);
    if (it != theMap.end()) {
      bfw.writeBitString(it->second);
    }
  }
  //dont forget to lookup 256 for the EOF marker, and write it out.
  map<unsigned, BitString>::const_iterator it = theMap.find(256);
  if (it != theMap.end()) {
    bfw.writeBitString(it->second);
  }
  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
  inF.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  uint64_t * counts = readFrequencies(argv[1]);
  Node * tree = buildTree(counts);
  delete[] counts;
  std::map<unsigned, BitString> theMap;
  BitString bs;
  tree->buildMap(bs, theMap);
  writeCompressedOutput(argv[1], argv[2], theMap);
  delete tree;
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this

  return EXIT_SUCCESS;
}

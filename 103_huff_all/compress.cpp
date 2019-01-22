#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"
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
  std::ifstream file;
  file.open(inFile);
  int c;
  std::map<unsigned, BitString>::const_iterator it;
  while ((c = file.get()) != EOF) {
    it = theMap.find(c);
    if (it != theMap.end()) {
      bfw.writeBitString(it->second);
    }
    else {
    }
  }
  it = theMap.find(256);
  bfw.writeBitString(it->second);  //EOF should be here anyway, if not can check
  file.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  uint64_t * counts = readFrequencies(argv[1]);
  assert(counts != NULL);
  Node * tree = buildTree(counts);
  delete[] counts;
  std::map<unsigned, BitString> theMap;
  BitString empty;
  tree->buildMap(empty, theMap);
  delete tree;
  writeCompressedOutput(argv[1], argv[2], theMap);
  return EXIT_SUCCESS;
}

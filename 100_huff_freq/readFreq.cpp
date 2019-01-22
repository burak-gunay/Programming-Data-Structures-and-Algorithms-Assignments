#include "readFreq.h"

#include <stdio.h>

#include <cstdio>
#include <cstdlib>
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
  FILE * fstream = fopen(fname, "r");
  if (fstream == NULL) {
    std::cerr << "Error opening the file, terminating";
    exit(EXIT_FAILURE);
  }
  uint64_t * freqArray = new uint64_t[257];
  for (int i = 0; i < 257; i++) {  //initialize all values to 0
    freqArray[i] = 0;
  }
  int c;
  while ((c = fgetc(fstream)) != EOF) {
    freqArray[c]++;
  }
  freqArray[256] = 1;  //manually assign to 0
  fclose(fstream);     //dont forget to close at the end
  return freqArray;
}

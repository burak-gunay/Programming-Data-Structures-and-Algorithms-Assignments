#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * fp;
  char * line = NULL;
  size_t len = 0;

  fp = fopen(filename, "r");

  counts_t * c = createCounts();

  while (getline(&line, &len, fp) != -1) {
    line[strlen(line) - 1] = '\0';
    char * my_val = lookupValue(kvPairs, line);

    //printf("%s\n", my_val);
    addCount(c, my_val);
  }
  free(line);

  fclose(fp);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    fprintf(stderr, "Terminating");
    exit(EXIT_FAILURE);
    // ALLAH BELANIZI VERSIN
  }

  kvarray_t * kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");

    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);

    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}

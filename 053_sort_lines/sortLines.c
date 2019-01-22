#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
int argc1() {
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz = 0;
  size_t i = 0;
  while ((getline(&curr, &sz, stdin) >= 0)) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
  return EXIT_SUCCESS;
}
int argc2(FILE * f) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz = 0;
  size_t i = 0;
  if (f == NULL) {
    fprintf(stderr, "Failure, exiting now");
    exit(EXIT_FAILURE);
  }
  while ((getline(&curr, &sz, f) >= 0)) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
  return EXIT_SUCCESS;
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    argc1();
    return EXIT_SUCCESS;
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * b = fopen(argv[i], "r");
      argc2(b);
      fclose(b);
    }
    return EXIT_SUCCESS;
  }
}

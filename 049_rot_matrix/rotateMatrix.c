#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void rotatematrix(FILE * f) {
  int c;
  char matrix[10][10];
  int i = 0;
  int j = 0;
  //int tempmatrix[10][10];
  while ((c = fgetc(f)) != EOF) {
    if (i == 10) {
      break;
    }
    else {
      if (c == '\n') {
        if (j != 10) {
          fprintf(stderr, "Early newline character");
          exit(EXIT_FAILURE);
        }
        i++;
        j = 0;
      }
      else {
        matrix[i][j] = c;
        j++;
      }
    }
  }
  if ((i != 10) || (j != 0)) {
    fprintf(stderr, "EOF not at proper location");
    exit(EXIT_FAILURE);
  }
  if (c != EOF) {
    fprintf(stderr, "Too many lines");
    exit(EXIT_FAILURE);
  }

  for (int a = 0; a < 10; a++) {
    for (int b = 0; b < 10; b++) {
      printf("%c", matrix[9 - b][a]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Uncorrect number of inputs in command line\n");
    exit(EXIT_FAILURE);  //Invalid inputs when calling the file
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "File was not opened correctly. Terminating\n");
    return EXIT_FAILURE;
  }
  rotatematrix(f);

  return EXIT_SUCCESS;
}

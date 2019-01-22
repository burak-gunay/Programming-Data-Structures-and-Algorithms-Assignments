#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int arrayMax(int * array, int n) {
  int i_max = 0;
  if (n <= 0) {
    return EXIT_FAILURE;
  }
  else {
    for (int i = 1; i < n; i++) {
      if (array[i] > array[i_max]) {
        i_max = i;
      }
    }
  }
  return i_max;
}

int freq(FILE * f) {
  int c;
  int freq[25];
  for (int b = 0; b < 25; b++) {
    freq[b] = 0;
  }
  while ((c = fgetc(f)) != EOF) {
    c = tolower(c);
    if (isalpha(c)) {
      for (int i = 97; i < 122; i++) {
        if (c == i) {
          freq[i - 97]++;
          //printf("%c's count is %d\n", c, freq[i - 97]);
        }
      }
    }
  }

  int max = arrayMax(freq, 25);
  //printf("%d", max);
  return (max + 97);
}

void breaks(int a) {
  for (int key = 0; key < 26; key++) {
    int c = 101;
    c = tolower(c);
    c -= 'a';
    c += key;
    c %= 26;
    c += 'a';
    if (a == c) {
      printf("%d\n", key);
      break;
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int a = freq(f);
  breaks(a);
  int close = fclose(f);
  if (close != 0) {
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

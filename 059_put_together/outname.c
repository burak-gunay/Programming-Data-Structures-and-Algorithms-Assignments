#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  if (inputName == NULL) {
    fprintf(stderr, "Incorrect read, terminating");
  }
  size_t c_length = strlen(".counts");
  size_t len = strlen(inputName);
  char * result = malloc(c_length + len + 1);
  result[0] = '\0';
  strcat(result, inputName);
  strcat(result, ".counts");
  return result;
}

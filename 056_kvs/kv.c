#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  FILE * kv = fopen(fname, "r");
  if (kv == NULL) {
    fprintf(stderr, "Could not read, terminating now");
    exit(EXIT_FAILURE);
  }
  kvarray_t * ans = malloc(sizeof(*ans));  //First malloc, pointer to kvarray_t
  if (ans == NULL) {
    fprintf(stderr, "Could not read, terminating now");
    exit(EXIT_FAILURE);
  }
  ans->currpair = NULL;
  ans->lenOfArray = 0;
  char * curr = NULL;
  size_t sz = 0;
  size_t i = 0;              //How many array values will be written
  char * equals_ptr = NULL;  //Pointer to the first equals
  char * newline_ptr = NULL;
  while ((getline(&curr, &sz, kv) >= 0)) {  //Curr malloc, can be freed each time called
    ans->lenOfArray = i + 1;
    ans->currpair =
        realloc(ans->currpair,
                ans->lenOfArray * sizeof(*ans->currpair));  //Realloc as it increases each time
    equals_ptr = strchr(curr, '=');
    newline_ptr = strchr(curr, '\n');
    ans->currpair[i] = NULL;  //When i=0, first array
    ans->currpair[i] =
        malloc(sizeof(*ans->currpair[i]));  //Third malloc //Mallocing single kvpair_t
    ans->currpair[i]->key = malloc((equals_ptr - curr + 1) * sizeof(char));
    ans->currpair[i]->value =
        malloc((newline_ptr - equals_ptr + 1) *
               sizeof(char));  //Keep them as char for testing, will change later

    strncpy(ans->currpair[i]->key, curr, equals_ptr - curr);
    ans->currpair[i]->key[equals_ptr - curr] = '\0';  //Assign end of string to null terminator

    strncpy(ans->currpair[i]->value, equals_ptr + 1, newline_ptr - equals_ptr - 1);
    ans->currpair[i]->value[newline_ptr - equals_ptr - 1] = '\0';
    i++;
  }
  free(curr);  //For the situation while's condition fails
  fclose(kv);
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->lenOfArray; i++) {  //For each malloc to kvpair
    free(pairs->currpair[i]->key);
    free(pairs->currpair[i]->value);
    free(pairs->currpair[i]);
  }
  free(pairs->currpair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->lenOfArray; i++) {
    printf("key = '%s' value = '%s'\n", pairs->currpair[i]->key, pairs->currpair[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (int i = 0; i < pairs->lenOfArray; i++) {
    int same = strcmp(pairs->currpair[i]->key, key);
    if (same == 0) {
      return pairs->currpair[i]->value;
    }
  }
  return NULL;
}

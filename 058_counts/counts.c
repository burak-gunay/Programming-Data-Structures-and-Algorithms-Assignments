#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * c = malloc(sizeof(*c));
  c->array_size = 0;
  c->unknown_count = 0;
  c->list_array = NULL;
  return c;
  //WRITE ME
}
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknown_count++;
    return;
  }
  if (c->list_array == NULL) {
    c->list_array = malloc(sizeof(*c->list_array));
    c->list_array->stringName = malloc(strlen(name) + 1);
    strcpy(c->list_array->stringName, name);
    c->list_array->numSeen = 1;
    c->array_size++;
    return;
  }
  for (size_t i = 0; i < c->array_size; i++) {
    if (strcmp(name, c->list_array[i].stringName) == 0) {
      c->list_array[i].numSeen++;
      return;
    }
  }
  c->array_size++;
  c->list_array = realloc(c->list_array, (c->array_size) * sizeof(*c->list_array));
  c->list_array[c->array_size - 1].stringName = malloc(strlen(name) + 1);
  strcpy(c->list_array[c->array_size - 1].stringName, name);
  c->list_array[c->array_size - 1].numSeen = 1;
}

void printCounts(counts_t * c, FILE * outFile) {
  if (outFile == NULL || c == NULL) {
    fprintf(stderr, "Invalid. Terminating");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < c->array_size; i++) {
    if (c->list_array[i].stringName == NULL) {
      fprintf(stderr, "Invalid. Terminating");
      exit(EXIT_FAILURE);
    }
    fprintf(outFile, "%s: %d\n", c->list_array[i].stringName, c->list_array[i].numSeen);
  }
  if (c->unknown_count > 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->unknown_count);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->array_size; i++) {
    free(c->list_array[i].stringName);
  }
  free(c->list_array);
  free(c);
}

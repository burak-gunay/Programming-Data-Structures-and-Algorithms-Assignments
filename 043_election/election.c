#include "election.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include any other headers you need here...

state_t parseLine(const char * line) {
  state_t stateread;
  const char * curr = line;  //curr will track where the pointer points at currently
  char * ptrfirst = NULL;    //Pointer to first :
  char * ptrlast = NULL;     //Pointer to last :
  ptrfirst = strchr(curr, ':');
  ptrlast = strrchr(curr, ':');
  if (curr == NULL || ptrlast == NULL || ptrfirst == NULL || ptrfirst == ptrlast) {
    fprintf(stderr, "Improper format, exiting now");
    exit(EXIT_FAILURE);
  }
  int i = 0;
  int j = 0;
  while (curr < ptrfirst) {
    stateread.name[i] = *curr;  //Assign each character until first : is reached
    curr++;
    i++;
  }
  stateread.name[i] = '\0';  //So the name string is valid
  curr += 1;                 //So curr is at the beginning of population(was at :)
  char pop[ptrlast - curr];  //Initialize the size of the pop string, to be converted into int
  while (curr < ptrlast) {
    pop[j] = *curr;
    curr++;
    j++;
  }
  pop[j] = '\0';                          //Again, valid string
  curr++;                                 //So curr is at the beginnning of electoral votes(was at:)
  stateread.population = atoi(pop);       //From string to integer
  stateread.electoralVotes = atoi(curr);  //From string to integer
  curr =
      line;  //Have these blocks, as memory for structs is overwritten. Double sure to avoid any error
  ptrfirst = NULL;
  ptrlast = NULL;
  return stateread;  //Returning the state
}
void check234(state_t * stateData,
              uint64_t * voteCounts,
              size_t nStates) {  //Checking if input is valid or not
  if (stateData == NULL || voteCounts == NULL || nStates <= 0) {
    fprintf(stderr, "Invalid values.Terminating");
    exit(EXIT_FAILURE);
  }
}
unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  uint sum = 0;
  check234(stateData, voteCounts, nStates);
  for (size_t i = 0; i < nStates; i++) {  //Changing the majority vote, and adding it to the sum
    if ((float)voteCounts[i] >
        (stateData[i].population) / (float)2) {  //Float to avoid value lost when int/int
      sum += stateData[i].electoralVotes;
    }
  }
  return sum;  //Returning the sum of electoral votes
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  check234(stateData, voteCounts, nStates);  //Like countElectoralvotes, checking valid input
  for (size_t i = 0; i < nStates; i++) {
    float temp = 0;
    temp = (voteCounts[i] / ((float)stateData[i].population)) *
           100;  //votes/statepopulation*100, gives percentage
    if (temp > 100) {
      fprintf(stderr, "Invalid number of votes. Are you trying to meddle with the election??");
      exit(EXIT_FAILURE);
    }
    if (temp >= 49.5 && temp <= 50.5) {
      printf(
          "%s requires a recount (Candidate A has %.2f%% of the vote)\n", stateData[i].name, temp);
    }
  }
  //STEP 3: write me
}
size_t arrayMax(
    float * array,
    size_t
        n) {  //Taken from assignment 035_arr_max, with a slight changes on parameters&return values
  size_t i_max = 0;
  if (n <= 0) {
    fprintf(stderr, "Invalid number of inputs");
    exit(EXIT_FAILURE);
  }
  else {
    for (size_t i = 1; i < n; i++) {
      if (array[i] > array[i_max]) {
        i_max = i;
      }
    }
  }
  return i_max;
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  check234(stateData, voteCounts, nStates);
  float temp[nStates];
  for (size_t i = 0; i < nStates; i++) {
    temp[i] = (voteCounts[i] / ((float)stateData[i].population)) * 100;
    if (temp[i] > 100) {
      fprintf(stderr, "Invalid number of votes. Are you trying to meddle with the election??\n");
      exit(EXIT_FAILURE);
    }
  }
  size_t final = arrayMax(
      temp,
      nStates);  //returns the index to the largest percentage, use that to reach stateData info
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[final].name, temp[final]);

  //STEP 4: write me
}

#include <stdio.h>

// EXTRA CREDIT - print the drexel dragon from the readme.md
extern void print_dragon(FILE *fptr){
  char readStr[128];

  while (fgets(readStr, sizeof(readStr), fptr) != NULL) {
      printf("%s", readStr);
  }

  printf("\n");
}
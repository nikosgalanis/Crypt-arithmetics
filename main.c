#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(void){
  initialize();                                                                 //get the words and initialize the strings
  all_letters();                                                                //create an array with all the letters
  if(!solve(0)) printf("Puzzle cannot be solved\n");                            //call solve function, and if it return 0, the puzzle cannot be solved
  return 0;
}

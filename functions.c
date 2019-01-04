#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

char first[2][10],second[2][10],result[2][10];                                  //store every word

char all[10];                                                                   //store all letters(max 10)
int values[10];                                                                 //store the value of each letter
int used[10]={0,0,0,0,0,0,0,0,0,0};                                             //store the digits and 0 or 1 if they are assigned or not
int total_count;                                                                //number of total letters

int solve(int current){                                                         //recursive function to solve the problem
  if(current==total_count-1){                                                   //base case
      for(int i=0;i<10;i++){
        if (!used[i]){                                                          //if number is not yet used
          assing_letter(current,i);                                             //asssign it to a letter
          if(check_if_solved()){                                                //if now the problem is solved, everythimg ok
            print_result();
            return 1;
          }
        }
      }
      return 0;                                                                 //if all letters are used, return 0
  }
  else{                                                                         //else, if we have more letters to assign
    for (int i=0;i<10;i++){
      if(!used[i]){                                                              //if it is not yet used
        assing_letter(current,i);                                               //asssign it
        used[i]=1;                                                              //note that is not available from now on
        if(solve(current+1)) return 1;                                          //call the function recursively for the next letter
        else used[i]=0;                                                         //else, if it return 0, backtrack
      }
    }
  return 0;
  } 
}

void initialize(void){                                                          //creates the 3 strings,one for each word;
  printf("Give the first word\n");
  scanf("%s",first[0]);
  int l1=strlen(first[0]);
  for (int i=0;i<l1;i++) first[1][i]=-1;                                         //suppose at the start each letter is assigned to -1
  printf("Give the second word\n");
  scanf("%s",second[0]);
  int l2=strlen(second[0]);
  for (int i=0;i<l2;i++) second[1][i]=-1;
  printf("Give the sum\n");
  scanf("%s",result[0]);
  int l3=strlen(result[0]);
  for (int i=0;i<l3;i++) result[1][i]=-1;
}

void all_letters(void){                                                         //create array with all the letters in the 3 words;
  int insert,not_found;
  int l1=strlen(first[0]), l2=strlen(second[0]), l3=strlen(result[0]);
  for(int i=0;i<l1;i++) all[i]= first[0][i];                                    //store all the letters of the first word
  int cnt=l1;
  for(int i=0;i<l2;i++) {                                                       //for every letter im second word
    not_found=0;
    if(found(second[0][i],all,cnt)==-1) not_found=1;                            //if we deo not find it in all[], store it
    if (not_found==1) all[cnt++]= second[0][i];
  }
  for(int i=0;i<l3;i++) {                                                       //same for the third
    not_found=0;
    if(found(result[0][i],all,cnt)==-1) not_found=1;
    if (not_found==1) all[cnt++]= result[0][i];
  }
  for(int i=0;i<cnt;i++) values[i]=-1;
  total_count=cnt;
}

int check_if_solved(void){                                                      //check if the puzzle is solved
  int l1=strlen(first[0]), l2=strlen(second[0]), l3=strlen(result[0]);
  int n1=letter_to_int(first[1],l1);
  int n2=letter_to_int(second[1],l2);
  int n3=letter_to_int(result[1],l3);
  if (n1+n2==n3) return 1;                                                      //adding the values so a+b=result in ints
  else return 0;
}

int letter_to_int(char* numbers,int n){                                         //converts the word into the integer that is produced by its digits
  int result=0,cnt=1;
  for(int i=n-1;i>=0;i--){
    result+=numbers[i]*cnt;
    cnt*=10;
  }
  return result;
}

int check_if_assigned(void){                                                    //check if all the letters are assigned to a digit
  for(int i=0;i<total_count;i++) if (values[i]==-1) return 0;
  return 1;
}

void assing_letter(int n,int i){                                                //assign digit i in the letter with possition n
  int flag=0,j;
      values[n]=i;                                                              //assign it, and if we find it in a word, change also the value in there
      j=found(all[n],first[0],total_count);
      if (j!=-1) first[1][j]=values[n];
      j=found(all[n],second[0],total_count);
      if (j!=-1) second[1][j]=values[n];
      j=found(all[n],result[0],total_count);
      if (j!=-1) result[1][j]=values[n];
  return;
}

int found(char letter, char*buff,int size){                                     //check if a letter is found into a buffer
  for(int i=0;i<size;i++) if (buff[i]==letter) return i;
  return -1;
}

void print_result(void){                                                        //print the result
  for(int i=0;i<total_count;i++)
    printf("%c=%d  ",all[i],values[i]);
    printf("\n");
}

void unassign_last_letter(int n){                                               //unassign the last choise
  int j;
  values[n]=-1;
  if((j=found(all[n],first[0],total_count))!=-1) first[1][j]=-1;                //if we find it in a word, remove its value from there
  if((j=found(all[n],second[0],total_count))!=-1) second[1][j]=-1;
  if((j=found(all[n],result[0],total_count))!=-1) result[1][j]=-1;
}

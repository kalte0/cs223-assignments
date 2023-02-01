/*
* a small program which turns a phrase into an acronym and prints the result. 
* 
* @author: Renata Del Vecchio
* @version: February 1, 2023
*/

#include <stdio.h>

/* 
* main function takes user input and makes an acronym of all 
* uppercase, initial letters.
*/
int main() {
  char buffer[64]; // buffer used for both user input & final acronym to save space.  
  buffer[0] = '\0'; // in case where scanf fails, while loop will terminate. 
  int numLetters = 0; // keeps track of how many letters are in the acronym.

  // user input:
  printf("Enter a phrase: "); 
  scanf("%[^\n]%*c", buffer); 

  int i = 0; 
  while (buffer[i] != '\0') { 
    // if it's a capital letter at the start of a word:
    if ((i == 0 || buffer[i-1] == ' ') && buffer[i] >= 41 && buffer[i] <= 90) { 
      buffer[numLetters] = buffer[i]; // add capital letter to start of word. 
      numLetters++; // increment the number of letters in acronym.
    } 
    i++; // increment through the user inputted phrase. 
  }
  buffer[numLetters] = '\0'; // add a end string character at the end. 

  printf("Your acronym is %s\n", buffer); 
  return 0;
}

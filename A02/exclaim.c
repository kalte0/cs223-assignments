/*
* program turns user input into an exclamation. 
* 
* @author: Renata Del Vecchio
* @version: February 1, 2023
*/

#include <stdio.h>
#include <stdlib.h>

/* 
* Main function reads user input and prints out an exclamation, including
* the original phrase with all lowercase letters turned to @, !, 
* #, or *. 
*/
int main() {
  char buff[32];
  buff[0] = '\0';
  char randomChars[4] = {'@', '!', '#', '*'};

  // user input: 
  printf("Enter a word: "); 
  scanf("%[^\n]%*c", buff); 

  // alter the user inputted string: 
  int i = 0; 
  while(buff[i] != '\0') { 
    if (buff[i] >= 97 && buff[i] <= 122) { // if char is lowercase letter:
      buff[i] = randomChars[rand()%4]; // replace with @, !, #, or *
    } 
	  i++; 
  }
  
  // print out altered statement. 
  printf("OMG! %s\n", buff); 

  return 0;
}

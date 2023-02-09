/*----------------------------------------------
 * Author: Renata Del Vecchio`
 * Date: 2-8-2023
 * Description A small program which converts user-input to ent speech. 
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  printf("Pause length: "); 
  int pauseLength; 
  // take user input to determine how many dots to write after each letter.
  scanf("%d", &pauseLength); 
  printf("Text: "); 
  char buffer[32];
  scanf("%s", buffer); // read a user inputted string to turn into ent speech. 
  // allocate enough memory to store the ent speech message:  
  char *slowMessage = malloc(strlen(buffer) + strlen(buffer)*pauseLength + 1); 
  int slowMessageIndex = 0; // stores index in slow message. 
  int i = 0; // stores index in the user-inputted string. 
  while (buffer[i] != '\0') { 
    slowMessage[slowMessageIndex++] = buffer[i]; // add letter from inputted string.
    for (int j = 0; j < pauseLength; j++ ) { 
      slowMessage[slowMessageIndex++] = '.'; // add appropriate amount of '.'s. 
    }
    i++; // look at the next letter in the user-inputted string.
  }
  slowMessage[slowMessageIndex] = '\0'; 
  printf("%s\n", slowMessage); 
  free(slowMessage); 
  return 0;
}

/***************************************************
 * mathgame.c
 * Author: Renata Del Vecchio 
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Welcome to Math Game!\n");
  printf("How many rounds do you want to play? ");
  int numRounds;
  scanf("%d", &numRounds);
  if (numRounds == 0) {
          printf("Alrighty! Thanks for not playing, I guess?\n");
          return 0;
  }
  int randomNum1, randomNum2;
  int numCorrect = 0;
  int playerAnswer;
  for (int i = 0; i < numRounds; i++ ) {
         randomNum1 = rand() % 9 + 1; // num 1-9 inclusive.    
         randomNum2 = rand() % 9 + 1; // num 1-9 inclusive. 
         printf("%d + %d = ? ", randomNum1, randomNum2); 
         scanf("%d", &playerAnswer);
         if (randomNum1 + randomNum2 == playerAnswer) {
                printf("Correct!\n\n");
		numCorrect++;
         }
         else { 
                printf("Incorrect >:( \n\n");
	 }
  }
  printf("You answered %d/%d correctly.\n", numCorrect, numRounds);
  return 0;
}

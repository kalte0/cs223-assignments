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

  // take user input.
  int numRounds;
  scanf("%d", &numRounds);

  if (numRounds == 0) {
    printf("Alrighty! Thanks for not playing, I guess?\n");
    return 0;
  }
 
  int randomNum1, randomNum2;
  int numCorrect = 0;
  int playerAnswer;

  for (int i = 0; i < numRounds; i++ ) { // play a [numRounds] number of rounds:
    randomNum1 = rand() % 9 + 1; // num 1-9 inclusive.    
    randomNum2 = rand() % 9 + 1; // num 1-9 inclusive. 
    printf("%d + %d = ? ", randomNum1, randomNum2); // prompt user with question 
    scanf("%d", &playerAnswer); // read user response.
    if (randomNum1 + randomNum2 == playerAnswer) { // if user correct:
      printf("Correct!\n\n");
      numCorrect++;
    }
    else { // if user wrong: 
      printf("Incorrect >:( \n\n");
    }
  } // end for

  printf("You answered %d/%d correctly.\n", numCorrect, numRounds);

  return 0;
}

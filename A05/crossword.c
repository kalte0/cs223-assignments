/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// structure which mimicks a Go "tuple", used for returning a set of indices.
struct tuple { 
  int val1; 
  int val2; 
};

/* 
* function which, given two words, returns the indices of the first letter  
* the two words have in common as a tuple.
* @param word1 the first word to find a common letter of. 
* @param word2 the second word to find a common letter of
* @return a tuple struct whose first value is the index in the first word
* of a common letter of the first letter the two words have in common. 
* The second value is the index in the second word of the first letter the two 
* words have in common. If there is no common letter, both values are -1.  
*/
struct tuple returnIndicesOfCommonLetter(char* word1, char* word2) { 
  struct tuple indices;
  // if there is no common letter, both indices will be -1. 
  indices.val1 = -1;
  indices.val2 = -1; 
  for (int i = 0; i < strlen(word1); i++ ) { 
    for (int j = 0; j < strlen(word2); j++ ) { 
      if (word1[i] == word2[j]) { 
        indices.val1 = i; 
        indices.val2 = j;
        return indices; 
      }
    }
  }
  return indices; 
}

/* 
* a function which prints a given 2d array.  
* @param array the 2d array to be printed. 
* @param rows the number of row of the 2s array. 
* @param cols the number of cols of the 2d array. 
*/
void printArray(char* array, int rows, int cols) { 
  for (int i = 0; i < rows; i++) { 
    for (int j = 0; j < cols; j++) { 
      printf("%c ", array[(i * cols) + j]); 
    }
    printf("\n"); 
  }
}

int main(int argc, char *argv[]) {
  // if not enough arguments have been provided: `
  if (argc < 3)  {
    printf("Usage: %s <word1> <word2>\n", argv[0]); // print an error message
    return(0); // and quit the program
  }
  // copy two words from the command line arguments
  char word1[64];
  strcpy(word1, argv[1]); 
  char word2[64]; 
  strcpy(word2, argv[2]);  

  // find the index in word1 and word2 of a common letter, if there is one. 
  struct tuple indices = returnIndicesOfCommonLetter(word1, word2);  
  if (indices.val1 == -1) { // if there is no common letter: 
    printf("No common letter!\n"); 
    return(0); 
  }
  else { // else, there is a common letter: 
    char* crosswordArray = malloc(strlen(word1) * strlen(word2)* sizeof(char)); 
    for (int i = 0; i < strlen(word1) * strlen(word2); i ++ ) { 
      crosswordArray[i] = '.'; // fill all spaces in the 2d array with '.''
    }  
    for (int i = 0; i < strlen(word1); i++) { // place word1 vertically in 2d array
      crosswordArray[indices.val2 + i*strlen(word2)] = word1[i]; 
    }
    for (int i = 0; i < strlen(word2); i++) { // print word2 horizontally in 2d array 
      crosswordArray[indices.val1*strlen(word2) + i] = word2[i]; 
    }
    printArray(crosswordArray, strlen(word1), strlen(word2)); // print the array.
    free(crosswordArray);
  }
  return 0;
}



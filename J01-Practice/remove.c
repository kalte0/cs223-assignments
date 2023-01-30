#include <stdio.h>
#include <string.h>

void removeLetter(char* str, char letter) { 
  for (int i = 0; i < strlen(str); i ++ ) { 
    if (str[i] == letter) { 
      for (int j = i; j < strlen(str); j ++ ) { 
        str[j] = str[j+1];  
      } 
    }
  }
}

int main() {
  char greeting[6]; 
  strcpy(greeting, "hello"); 
  removeLetter(greeting, 'e'); 
  printf("%s\n", greeting); 
  return 0;
}

#include <stdio.h>
#include <string.h>

int isPalindrome(char* str) {
  for (int i = 0; i < strlen(str)/2; i ++ ) { 
    if (str[i] != str[strlen(str) - i - 1]) { 
      return 0; 
    } 
  }
  return 1; 
}

int main() {
  char* str1 = "racecar"; 
  char* str2 = "IpalindromeI"; 
  printf("isPalindrome(%s) is %d\n", str1, isPalindrome(str1)); 
  printf("isPalindrome(%s) is %d\n", str2, isPalindrome(str2)); 
  return 0;
}

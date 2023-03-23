/*----------------------------------------------
 * Author: Renata Del Vecchio
 * Date: 3/22/2023
 * A program which spawns child processes. 
 ---------------------------------------------*/

#include <stdio.h>
#include <unistd.h>

int main() {
  printf("%d] A0\n", getpid()); // print the pid of the current process. 
  pid_t pid = fork(); // fork for the first time-- creating a child process 
  if (pid == 0) { // if this is a child routine: 
    printf("%d] B1\n", getpid()); 
  }
  else { // if the parent routine:
    printf("%d] B0\n", getpid()); 
    pid = fork(); // fork for the second time-- creating a child process
    if (pid == 0) { // if this is a child routine: 
      printf("%d] C1\n", getpid()); 
    }
    else { // if this is the parent process.
      printf("%d] C0\n", getpid()); 
    } 
  }
  printf("%d] Bye\n", getpid()); // all processes should print "Bye."
  return 0;
}

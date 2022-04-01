#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  while (1) {
    char *cmd= read_command();
    int pid;

    if ( (pid=fork()) == 0) {
      exec (cmd);
    }
    else {
      wait (pid);
    }
  }
}

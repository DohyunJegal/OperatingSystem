#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int signum){
  printf("Caught signal %d\n", signum);
  exit(signum);
}

int main(){
  signal(SIGINT, signal_handler);

  while(1){
    printf("Program processing here.\n");
    sleep(1);
  }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	pid = fork();
	
	if (pid < 0){ 
		fprintf(stderr, "Fork Failed \n");
		exit(-1);
	}
	else if (pid == 0){
		execlp("/bin/ls", "ls", NULL);
	}
	else{
		wait (NULL);
		printf("Child Complete \n");
		exit(0);
	}
}

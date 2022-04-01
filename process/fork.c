#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int pid;
	int status;

	pid = fork();
	if (pid < 0){
		fprintf(stderr, "Fork Failed");
		exit(-1);
	}
	else if (pid == 0){
		printf("Child: %d Parent: %d\n", getpid( ), getppid( ));
		exit(3);
	}
	else{ 
		wait(&status);
		printf("Parent: %d Child: %d\n", getpid( ), pid);
		printf("Status : %d\n", status>>8);
	}
	return 0;
}

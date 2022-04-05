#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <ctype.h>
#define MAXMSGLEN 256

sem_t sem1;
sem_t sem2;
char msg1[MAXMSGLEN];
char msg2[MAXMSGLEN];
void* threadFunc1(void *arg);
void toggleCase(char *buf);

int main(){
	pthread_t thread1;
	char argmsg1[]="Thread1: ";
	int res;
	int thNum;

	res = sem_init(&sem1, 0, 0);
	res = sem_init(&sem2, 0, 0);
	res = pthread_create(&thread1, NULL, threadFunc1,argmsg1);

	while(1){
		printf("Print message to send:\n");
		fgets(msg1, MAXMSGLEN, stdin);
		sem_post(&sem1); // V 연산(signal 연산)
		/****** 대기****/
		sem_wait(&sem2); // P 연산
		printf("Respmessage: %s \n",msg2);
	}
	return 0;
}

void* threadFunc1(void *arg){
	printf("I am :%s \n",arg);
	while(1)
	{
	sem_wait(&sem1);
	strcpy(msg2,msg1);
	toggleCase(msg2);
	sem_post(&sem2);
	}
}

void toggleCase(char *str){
	while(*str){
		if (isupper(*str))
			*str= tolower(*str);
		else if (islower(*str))
			*str= toupper(*str);
		str++;
	}
}

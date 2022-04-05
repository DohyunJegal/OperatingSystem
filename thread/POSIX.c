#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;
void *runner(void *param);

int main(int argc, char** argv){
	pthread_t tid;	// 쓰레드
	pthread_attr_t attr;	// 쓰레드 속성 구조체

	if (argc != 2) {
		fprintf(stderr, "Usage: a.out<integer value>\n");
	return -1;
	}
	
	if (atoi(argv[1]) < 0) {
		fprintf(stderr, "%d must be >= 0 \n", atoi(argv[1]));
		return -1;
	}

	pthread_attr_init(&attr);	// 쓰레드 속성 구조체 생성 및 초기화
	pthread_create(&tid, &attr, runner, argv[1]);	// 새로운 쓰레드 생성
	pthread_join(tid, (void **)NULL);	// 지정 쓰레드 종료시 까지 대기

	printf("sum = %d\n", sum);
}

void *runner(void *param) {
	int i, upper = atoi(param);
	sum = 0;

	for (i= 1; i<= upper; i++)
		sum += i;

	pthread_exit(0);	// 호출 쓰레드 종료
}

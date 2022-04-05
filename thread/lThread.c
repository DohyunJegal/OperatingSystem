#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/sched.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define STACK_SIZE (1024 * 1024)	// 복사된 자식노드 배열 사이즈

static int childFunc(void *arg){	// 복사된 자식노드용 함수
	struct utsname uts;
	
	if (sethostname(arg, strlen(arg)) == -1)	// 자식노드의 UTS 네임스페이스에서 호스트 이름 변경
		errExit("sethostname");
		
	if (uname(&uts) == -1)	// 호스트 이름 검색 및 표시
		errExit("uname");
	printf("uts.nodename in child: %s\n", uts.nodename);

	sleep(200);
	return 0;	// 자식노드 종료
}

int main(int argc, char *argv[]){
	char *stack;	// 스택 버퍼의 시작
	char *stackTop; // 스택 버퍼의 끝
	pid_t pid;
	struct utsname uts;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <child-hostname>\n", argv[0]);
		exit(EXIT_SUCCESS);
	}

	stack = malloc(STACK_SIZE); // 자식노드 스택 할당

	if (stack == NULL)
		errExit("malloc");

	stackTop = stack + STACK_SIZE;
	pid = clone(childFunc, stackTop, CLONE_NEWUTS | SIGCHLD, argv[1]);

	if (pid == -1)
		errExit("clone");
	printf("clone() returned %ld\n", (long) pid);

	// 부모 노드가 여기로 넘어옴
	sleep(1); // 하위 항목에 호스트 이름 변경 시간 제공

	if (uname(&uts) == -1)
		errExit("uname");
	printf("uts.nodename in parent: %s\n", uts.nodename);

	if (waitpid(pid, NULL, 0) == -1) // 자식노드 대기
		errExit("waitpid");
	printf("child has terminated\n");

	exit(EXIT_SUCCESS);
}

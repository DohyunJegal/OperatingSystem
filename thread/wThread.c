#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>

DWORD WINAPI ThreadFunction(void* arg);

int main(){
	HANDLE hThread;	// 쓰레드 핸들
	DWORD dwThreadID, dw;	// 쓰레드 ID
	hThread = (HANDLE)_beginthreadex(NULL,0,(unsigned int(__stdcall*)(void*))ThreadFunction, NULL, 0, (unsigned*)&dwThreadID);

	if (hThread == 0) {
		puts("_beginthreadex() error");
		exit(1);
	}

	printf("생성된 쓰레드 핸들: %d\n",hThread);	// id를 포인터로 관리
	printf("생성된 쓰레드 ID : %d\n",dwThreadID);
	dw = WaitForSingleObject(hThread,3000); // 쓰레드가 종료할 때까지 대기, 3초 초과시 종료

	if (dw == WAIT_FAILED) {
		puts("쓰레드의 비정상적인 종료");
		exit(1);
	}
	else {
		printf("main 함수종료, %s종료\n", (dw == WAIT_OBJECT_0)?"정상":"비정상");
	}
	return 0;
}

DWORD WINAPI ThreadFunction(void* arg) {
	int i;

	for (i = 0; i < 5; i++) {
		Sleep(500);
		printf("쓰레드 실행중%d \n",i);
	}
	return 0;
}

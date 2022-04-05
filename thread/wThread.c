#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>

DWORD WINAPI ThreadFunction(void* arg);

int main(){
	HANDLE hThread;
	DWORD dwThreadID, dw;
	hThread= (HANDLE)_beginthreadex(NULL,0,(unsigned int(__stdcall*)(void*))ThreadFunction, NULL, 0, (unsigned*)&dwThreadID);

	if (hThread==0) {
		puts("_beginthreadex() error");
		exit(1);
	}

	printf("�����Ⱦ������ڵ�: %d\n",hThread);
	printf("�����Ⱦ�����ID : %d\n",dwThreadID);
	dw= WaitForSingleObject(hThread,3000); // �����尡�����Ҷ��������, ��3���ʰ�������

	if (dw== WAIT_FAILED) {
		puts("�������Ǻ�������������");
		exit(1);
	}
	else {
		printf("main �Լ�����, %s����\n", (dw==WAIT_OBJECT_0)?"����":"������");
	}
	return 0;
}

DWORD WINAPI ThreadFunction(void* arg) {
	int i;

	for (i=0; i< 5; i++) {
		Sleep(500);
		printf("�����������%d \n",i);
	}
	return 0;
}

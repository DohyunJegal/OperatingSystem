#include<stdio.h>
#include<windows.h>

int main( ) {
	STARTUPINFO si; 
	PROCESS_INFORMATION pi; 
	const char *command = "C:\\Windows\\notepad.exe"; 
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if(!CreateProcess(NULL, 
		(LPSTR)command, 
		NULL,
		NULL, 
		FALSE, 
		0, 
		NULL, 
		NULL, 
		&si, 
		&pi))
	{
		fprintf(stderr, "Create Process Failed");
		return -1;
	}

	WaitForSingleObject(pi.hProcess, INFINITE); 
	printf("Child Complete");

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

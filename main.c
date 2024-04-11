#include <windows.h>
#include <signal.h>
#include <stdlib.h>

HHOOK hookHandle;

void ctrllc(int sig) {
	UnhookWindowsHookEx(hookHandle);
	exit(0);
}

int main() {
	HMODULE wmDll = LoadLibraryW(L"wm_dll");
	FARPROC shellProc = GetProcAddress(wmDll, "ShellProc");
	
	hookHandle = SetWindowsHookExW(WH_SHELL, shellProc, wmDll, 0);	
	
	signal(SIGINT, ctrllc);

	for(;;) {}
}

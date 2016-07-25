// AntiDebug-5.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include  <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	typedef unsigned long (__stdcall *pfnNtQueryInformationProcess)(IN  HANDLE, 
        IN  unsigned int, OUT PVOID, IN ULONG, OUT PULONG);

	pfnNtQueryInformationProcess NtQueryInfoProcess = NULL;
	
	HMODULE hmod = LoadLibrary(L"ntdll.dll");

	UINT32 debugFlag;
	
	NtQueryInfoProcess =  (pfnNtQueryInformationProcess)GetProcAddress(hmod,"NtQueryInformationProcess");
	
    unsigned int status = (NtQueryInfoProcess) (GetCurrentProcess(), 0x1f, &debugFlag, 4, NULL); // 31 (0x1F) = DebugProcessFlags

	if (debugFlag == 0x00000000){
		printf("Debugger detected\n");
	}else{
		printf("Debugger not detected\n");
	}

}




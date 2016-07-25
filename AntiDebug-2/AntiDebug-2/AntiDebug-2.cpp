// AntiDebug-2.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <windows.h>
#include <Winternl.h>




int _tmain(int argc, TCHAR* argv[])
{

// Function Pointer Typedef for NtQueryInformationProcess
typedef unsigned long (__stdcall *pfnNtQueryInformationProcess)(IN  HANDLE, 
        IN  unsigned int, OUT PVOID, IN ULONG, OUT PULONG);

pfnNtQueryInformationProcess NtQueryInfoProcess = NULL;

const int ProcessObject = 0x1e;
const int DebugParameter = 0x1f;

const int debugFlag=0;

unsigned int  status;

	HANDLE hDebugObject;
	HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));
	NtQueryInfoProcess = (pfnNtQueryInformationProcess)
   
	GetProcAddress(hNtDll, "NtQueryInformationProcess");


status  = NtQueryInfoProcess (GetCurrentProcess(), ProcessObject, &hDebugObject, 4, NULL); // 0x1e is the enum for

printf("DebugFlag is %d\n" , debugFlag);

if (hDebugObject){
	printf("Debugger detected with 0x1e\n");
}
else{
	printf("Debugger NOT detected with 0x1e\n");
}

}
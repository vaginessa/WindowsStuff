// AntiDebug.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <windows.h>

LONG WINAPI UnhandledExcepFilter(PEXCEPTION_POINTERS pExcepPointers)
{
    // Restore old UnhandledExceptionFilter
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)
          pExcepPointers->ContextRecord->Eax);

    // Skip the exception code
    pExcepPointers->ContextRecord->Eip += 2;

    return EXCEPTION_CONTINUE_EXECUTION;
}

int _tmain(int argc, _TCHAR* argv[])
{
       ::SetUnhandledExceptionFilter(UnhandledExcepFilter);
    __asm{xor eax, eax}
    __asm{div eax}

	printf("Debugger not detected\n");
    // Execution resumes here if there is no debugger
    // or if there is a debugger it will never
    // reach this point of execution
	int a;
	getchar();
}
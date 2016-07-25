// AntiDebug-3-v2.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <windows.h>
#include <excpt.h>
#include <stdio.h>
#include <iostream>



BOOL anti_debug_flag = TRUE;



LONG WINAPI UnhandledExcepFilter(PEXCEPTION_POINTERS pExcepPointers)
{
    // Restore old UnhandledExceptionFilter
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)
          pExcepPointers->ContextRecord->Eax);

    // Skip the exception code
    anti_debug_flag = FALSE;

    return EXCEPTION_CONTINUE_EXECUTION;
}



int _tmain(int argc, _TCHAR* argv[])
{
	SetUnhandledExceptionFilter(UnhandledExcepFilter);  // breaks the W xor X! 

	__asm 
		{ 
			pushfd
			or dword ptr ss:[esp+1], 1	// or dword ptr ss:[esp], 0x100
			popfd
			nop
		}

	if(anti_debug_flag == FALSE){
		printf("Debugger not detected\n");
	}
	else{
		printf("Debugger detectecd\n");
	}

	getchar();


}






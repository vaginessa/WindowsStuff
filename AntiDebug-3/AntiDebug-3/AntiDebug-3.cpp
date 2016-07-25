// AntiDebug-3.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <windows.h>
#include <excpt.h>
#include <stdio.h>


BOOL anti_debug_flag = TRUE;

void fuckyou(){

			__try{

		__asm 
		{ 
			pushfd
			or dword ptr ss:[esp+1], 1	// or dword ptr ss:[esp], 0x100
			popfd
			nop
		}
		
	}
		__except(EXCEPTION_CONTINUE_SEARCH){
					
		}

}


void anti_debug()
{
	__try
	{
		fuckyou();
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		anti_debug_flag = FALSE;
	}
}


void happy(){
   printf("I am happy\n");
}
int _tmain(int argc, _TCHAR* argv[])
{
	anti_debug();

	if(anti_debug_flag)
		printf("Debugger Detected\n");
	else
		printf("No Debugger...\n");
		happy();
	return 0;
}





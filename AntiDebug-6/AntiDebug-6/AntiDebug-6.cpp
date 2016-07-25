// AntiDebug-6.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{

	BOOL debug = FALSE;
	CheckRemoteDebuggerPresent(GetCurrentProcess(), &debug);

	if(debug == TRUE){
		printf("Debugger detected\n");
	}
	else
	{
		printf("Debugger NOT detected\n");
	}

}


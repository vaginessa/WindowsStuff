// AntiDebug-4.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	OutputDebugStringA("aaaaa");


__try{

__asm mov ebx, dword ptr [eax] //if not debugged it will raise an exception cause eax will be 0 or 1

cout << "debugger found" << endl;
}


__except(EXCEPTION_EXECUTE_HANDLER)
{
	cout << "no debugger" << endl;	
}

system ("pause");

return 0;
}




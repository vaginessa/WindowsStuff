// multi_heap_code.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


char code[50];

char code2[50];

char code3[50];

char data[5]  = "\x41\x41\x41\x41"; 


LPVOID get_exit(){

	HMODULE hmod_libname;
	LPVOID exit_process_address;

	hmod_libname = LoadLibraryA("kernel32.dll");

	if(hmod_libname == NULL)
	{
		printf("Error: could not load library!\n");
		exit(-1);
	}
	exit_process_address = GetProcAddress(hmod_libname,"ExitProcess");
	
	if(exit_process_address == NULL)
	{
		printf("Error: could find the function in the library!\n");
		exit(-1);
	}

	return exit_process_address;
}



void craft_code(LPVOID address_data, LPVOID address_code, LPVOID address_code_2,  LPVOID address_code_3 , LPVOID exit_address){

	//printf("code at %08x\n", code);

	memcpy(code,"\x83\xC0\x01\x83\xC0\x02\xA1",7);

    // i.e. 0x08048776
	char byte_0 =  (unsigned int)address_data & 0x000000ff;		   // i.e. 0x76
	char byte_1 = ((unsigned int)address_data & 0x0000ff00) >> 8;  // i.e. 0x87
	char byte_2 = ((unsigned int)address_data & 0x00ff0000) >> 16; // i.e. 0x04
	char byte_3 = ((unsigned int)address_data & 0xff000000) >> 24; // i.e. 0x08

	/*
	printf("byte_0: %02x\n",byte_0);
	printf("byte_1: %02x\n",byte_1);
	printf("byte_2: %02x\n",byte_2);
	printf("byte_3: %02x\n",byte_3);
	*/

	memcpy(code+7, &byte_0, 1);
	memcpy(code+8, &byte_1, 1);
	memcpy(code+9, &byte_2, 1);
	memcpy(code+10,&byte_3, 1);

	// now we are going to call an address in the heap_zone_code_2 
	memcpy(code+11,"\xB8",1); // mov eax, <heap_2_address>

	byte_0 =  (unsigned int)address_code_2 & 0x000000ff;		// i.e. 0x76
	byte_1 = ((unsigned int)address_code_2 & 0x0000ff00) >> 8;  // i.e. 0x87
	byte_2 = ((unsigned int)address_code_2 & 0x00ff0000) >> 16; // i.e. 0x04
	byte_3 = ((unsigned int)address_code_2 & 0xff000000) >> 24; // i.e. 0x08

	/*
	printf("byte_0: %02x\n",byte_0);
	printf("byte_1: %02x\n",byte_1);
	printf("byte_2: %02x\n",byte_2);
	printf("byte_3: %02x\n",byte_3);
	*/

	memcpy(code+12, &byte_0, 1);
	memcpy(code+13, &byte_1, 1);
	memcpy(code+14, &byte_2, 1);
	memcpy(code+15, &byte_3, 1);
   
	memcpy(code+16,"\xFF\xD0",2); // call eax 


	// now crafting the heap_code_2

	memcpy(code2,"\xB8",1); // mov

	byte_0 =  (unsigned int)address_data & 0x000000ff;		   // i.e. 0x76
	byte_1 = ((unsigned int)address_data & 0x0000ff00) >> 8;  // i.e. 0x87
	byte_2 = ((unsigned int)address_data & 0x00ff0000) >> 16; // i.e. 0x04
	byte_3 = ((unsigned int)address_data & 0xff000000) >> 24; // i.e. 0x08

	memcpy(code2+1, &byte_0, 1);
	memcpy(code2+2, &byte_1, 1);
	memcpy(code2+3, &byte_2, 1);
	memcpy(code2+4, &byte_3, 1);

	memcpy(code2+5,"\xB3\x41",2); // mov bl,0x41
	memcpy(code2+7,"\x01\x58\x01",3); // add [eax],bl   modify the data in heap_data 

	memcpy(code2+10,"\xB8",1); // mov eax, <heap_3_address>

	byte_0 =  (unsigned int)address_code_3 & 0x000000ff;		// i.e. 0x76
	byte_1 = ((unsigned int)address_code_3 & 0x0000ff00) >> 8;  // i.e. 0x87
	byte_2 = ((unsigned int)address_code_3 & 0x00ff0000) >> 16; // i.e. 0x04
	byte_3 = ((unsigned int)address_code_3 & 0xff000000) >> 24; // i.e. 0x08

	memcpy(code2+11, &byte_0, 1);
	memcpy(code2+12, &byte_1, 1);
	memcpy(code2+13, &byte_2, 1);
	memcpy(code2+14, &byte_3, 1);
   
	memcpy(code2+15,"\xFF\xD0",2); // call eax 

	// Crafting a clean exit 
	memcpy(code3,"\x31\xD2\x50\xB8",4);

	// Transforming to little endian the address of exit 
	byte_0 =  (unsigned int)exit_address & 0x000000ff;		  // i.e. 0x76
	byte_1 = ((unsigned int)exit_address & 0x0000ff00) >> 8;  // i.e. 0x87
	byte_2 = ((unsigned int)exit_address & 0x00ff0000) >> 16; // i.e. 0x04
	byte_3 = ((unsigned int)exit_address & 0xff000000) >> 24; // i.e. 0x08

	/*
	printf("byte_0: %02x\n",byte_0);
	printf("byte_1: %02x\n",byte_1);
	printf("byte_2: %02x\n",byte_2);
	printf("byte_3: %02x\n",byte_3);
	*/

	memcpy(code3+4, &byte_0, 1);
	memcpy(code3+5, &byte_1, 1);
	memcpy(code3+6, &byte_2, 1);
	memcpy(code3+7, &byte_3, 1);

	// call eax 
	memcpy(code3+8,"\xFF\xD0",2);

	// copy code on the heap 
	memcpy(address_code,code,sizeof(code));	
	memcpy(address_code_2,code2,sizeof(code2));
	memcpy(address_code_3,code3,sizeof(code3));
}

int _tmain(int argc, _TCHAR* argv[])
{
	 
	LPVOID address_code   = VirtualAlloc(NULL,20000, MEM_COMMIT | MEM_RESERVE , PAGE_EXECUTE_READWRITE ); // for the code 
	LPVOID dummyspace     = VirtualAlloc(NULL,20000, MEM_COMMIT | MEM_RESERVE , PAGE_EXECUTE_READWRITE ); // dummy allocation 
	LPVOID address_data   = VirtualAlloc(NULL,20000, MEM_COMMIT | MEM_RESERVE , PAGE_EXECUTE_READWRITE ); // for the data 
	LPVOID address_code_2 = VirtualAlloc(NULL,20000, MEM_COMMIT | MEM_RESERVE , PAGE_EXECUTE_READWRITE ); // for the other code zone 
	LPVOID address_code_3 = VirtualAlloc(NULL,20000, MEM_COMMIT | MEM_RESERVE , PAGE_EXECUTE_READWRITE ); // for the exitcode zone 

	if(address_code == NULL || dummyspace == NULL || address_data == NULL || address_code_2 == NULL ){
		printf("Something went wrong during allocation on the heap\n");
		exit(0);
	}
	
	// The allocation should be all disjunted since we want 3 different heapzones 
	printf("Allocations:\naddress_code: %08x - %08x \naddress_code_2: %08x - %08x \naddress_code_3: %08x - %08x \ndummyspace: %08x - %08x \naddress_data: %08x - %08x\n", address_code, (unsigned int)address_code + 0x5000 , address_code_2, (unsigned int)address_code_2 + 0x5000, address_code_3, (unsigned int)address_code_3 + 0x5000, dummyspace, (unsigned int)dummyspace+0x5000, address_data, (unsigned int)address_data+0x5000 );

	memcpy(address_data,data,sizeof(data));
	
	LPVOID exit_address = get_exit();

	craft_code(address_data,address_code, address_code_2 , address_code_3 ,exit_address);


	int (*func)(void) = (int(*)(void))address_code;
	int num = func();

}


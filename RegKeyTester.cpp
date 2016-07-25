#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

void QueryKey(HKEY hKey) 
{ 
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 
 
    DWORD i, retCode; 
 
    TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 
 
    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 
 
    // Enumerate the subkeys, until RegEnumKeyEx fails.
    
    if (cSubKeys)
    {
        printf( "\nNumber of subkeys: %d\n", cSubKeys);

        for (i=0; i<cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                     achKey, 
                     &cbName, 
                     NULL, 
                     NULL, 
                     NULL, 
                     &ftLastWriteTime); 
            if (retCode == ERROR_SUCCESS) 
            {
                _tprintf(TEXT("(%d) %s\n"), i+1, achKey);
            }
        }
    } 
 
    // Enumerate the key values. 

    if (cValues) 
    {
        printf( "\nNumber of values: %d\n", cValues);

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
        { 
            cchValue = MAX_VALUE_NAME; 
            achValue[0] = '\0'; 
            retCode = RegEnumValue(hKey, i, 
                achValue, 
                &cchValue, 
                NULL, 
                NULL,
                NULL,
                NULL);
 
            if (retCode == ERROR_SUCCESS ) 
            { 
                _tprintf(TEXT("(%d) %s\n"), i+1, achValue); 
            } 
        }
    }
}



/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	HKEY hKey;
	LPCTSTR sk = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	
	LONG openRes = RegOpenKeyEx(HKEY_CURRENT_USER, sk, 0, KEY_ALL_ACCESS , &hKey);
	
	if (openRes==ERROR_SUCCESS) {
    printf("Success opening key.");
	} else {
	    printf("Error opening key.");
	}
	
	// Case (1) - inserting a new key 
	// Inserting a new value inside the registry 
	
	QueryKey(hKey);
	
	printf("Adding a new regkey inside \"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\"\n");
	
	LPCTSTR value = TEXT("SomeKey");
	LPCTSTR data = TEXT("ReadOnlyData\0");
	

	LONG setRes = RegSetValueEx (hKey, value, 0, REG_SZ, (LPBYTE)data, strlen(data)+1);
	
	if (setRes == ERROR_SUCCESS) {
	    printf("Success writing to Registry\n");
	} else {
	    printf("Error writing to Registry\n");
	    exit(0);
	}
	
	QueryKey(hKey);
	
	// Case (2) - inserting a new key and modofing it 
	
	// Adding another regkey that will be modified 
	
	value = TEXT("SomeKey2");
	data = TEXT("WriteData\0");

	setRes = RegSetValueEx (hKey, value, 0, REG_SZ, (LPBYTE)data, strlen(data)+1);
	
	if (setRes == ERROR_SUCCESS) {
	    printf("Success writing to Registry\n");
	} else {
	    printf("Error writing to Registry\n");
	    exit(0);
	}
	
	data = TEXT("WriteData_overwritten\0");
	
	// Modyfing the last inserted regkey 
	setRes = RegSetValueEx (hKey, value, 0, REG_SZ, (LPBYTE)data, strlen(data)+1);
	
	QueryKey(hKey);
	
	// Case (3) - modifing an existing regkey 
	
	sk = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
	
	openRes = RegOpenKeyEx(HKEY_CURRENT_USER, sk, 0, KEY_ALL_ACCESS , &hKey);
	
	if (openRes==ERROR_SUCCESS) {
    printf("Success opening key.");
	} else {
	    printf("Error opening key.");
	}
	
	value = TEXT("User Agent\0");
	
	// default value = 875dbbb8a64ff2f1, changing it to deadbeef
	data = TEXT("deadbeef\0");
	
	
	// changing value from 1 to 0
	setRes = RegSetValueEx (hKey, value, 0, REG_SZ, (LPBYTE)data, strlen(data)+1);
	
	if (setRes == ERROR_SUCCESS) {
	    printf("Success writing to Registry\n");
	} else {
	    printf("Error writing to Registry\n");
	    exit(0);
	}
	
	
	
	
}

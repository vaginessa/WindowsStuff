#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <urlmon.h>
#include <Wininet.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")

using namespace std;


typedef HRESULT (* def_URLDownloadToFile)(LPUNKNOWN pCaller,  LPCTSTR szURL, LPCTSTR szFileName,DWORD dwReserved, LPBINDSTATUSCALLBACK lpfnCB);

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
  // Creating and writing a new file 
  std::ofstream myfile;
  
  myfile.open("./malwaaaaaaaaaaaaaaaaa.txt");
  myfile << "esr09rys87e587se85wfh985hfaw7yh8wyhf75diewhy4ydiwhei4daewhi4daiwehyaey%&/()==IJH&G%&/H(JD).\n";
  myfile.close();
  
  // writing an existing file on the machine 
  std::ofstream farojpg;
    
  farojpg.open("C:\\Users\\Public\\Pictures\\Sample\ Pictures\\Faro.jpg");
  farojpg << "BHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaaaaa.\n";
  farojpg.close();
  
  printf("Overwritten existing file success!\n");
  
  // reading an existing file
  string line;
  ifstream another_file ("C:\\Windows\\notepad.exe");
  int count = 0;
  if (another_file.is_open())
	{
	    while ( getline(another_file,line) )
		 {
		 count++;
		 }
    another_file.close();
  }
  
  printf("Read file, %d lines\n",count);
  
  count = 0;
  // reading a previously written file 
  ifstream thejpg ("C:\\Users\\Public\\Pictures\\Sample\ Pictures\\Faro.jpg");
  count = 0;
  if (thejpg.is_open())
	{
	    while ( getline(thejpg,line) )
		 {
		 count++;
		 }
    thejpg.close();
  }
  
  printf("Read the jpg file, %d lines\n",count);
  
  // malwaaaaaaaaa should figure as 'dropped'
  
  if( remove( "./malwaaaaaaaaaaaaaaaaa.txt" ) != 0 )
    perror( "Error deleting file" );
  else
    puts( "File successfully deleted" );
    
}

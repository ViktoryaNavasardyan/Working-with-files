#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

using namespace std;

void print_error_message()
{
	TCHAR* buffer;
	DWORD error_code = GetLastError();

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, error_code, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), (LPTSTR)&buffer, 0, NULL);
	_tprintf(_T("%s\n"), buffer);
	LocalFree(buffer);
}
int _tmain(int argc, TCHAR* argv[])
{
	if (argc != 2) cout << "error in arguments\n";
	else
	{
		HANDLE h = CreateFile(argv[1], FILE_WRITE_ATTRIBUTES, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (h == INVALID_HANDLE_VALUE) print_error_message();
		else
		{
			
			FILETIME c, a, w; 
			SYSTEMTIME c1, w1;
			GetFileTime(h, &c, &a, &w);
			FileTimeToSystemTime(&c, &c1);
			cout << "creation year = " << c1.wYear << endl << "month = " << c1.wMonth << endl << "day = " << c1.wDay << endl;
			c1.wDay = 23;
			c1.wMonth = 9;
			SystemTimeToFileTime(&c1, &c);
			SetFileTime(h, &c, &a, &w);
			
			CloseHandle(h);
		}
	}

	return 0;
}

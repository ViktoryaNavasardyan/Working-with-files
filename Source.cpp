#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <stdio.h>

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

//int _tmain(int argc, TCHAR* argv[])
//{
//	if (argc != 2) cout << "error in arguments\n";
//	else
//	{
//		WIN32_FIND_DATA a;
//		HANDLE f;
//		SYSTEMTIME temp;
//		if (!SetCurrentDirectory(argv[1])) print_error_message();
//		else
//		{
//			wcout << "current directory is:" << argv[1] << endl;
//			f = FindFirstFile(TEXT("*.txt"), &a);
//			if (f == INVALID_HANDLE_VALUE) print_error_message();
//			else
//			{
//				cout << endl;
//				wcout << "filename is:" << a.cFileName << endl;
//				if (!SetFileAttributes(a.cFileName, FILE_ATTRIBUTE_HIDDEN)) print_error_message();
//				else {
//					while (FindNextFile(f, &a))
//					{
//						cout << endl;
//						wcout << "filename is:" << a.cFileName << endl;
//						if (!SetFileAttributes(a.cFileName, FILE_ATTRIBUTE_HIDDEN)) print_error_message();
//					}
//					FindClose(f);
//				}
//			}
//		}
//	}
//	return 0;
//}
//"C:\\Projects\\OS_mijankyal"

int _tmain(int argc, TCHAR* argv[])
{
	if (argc != 4) cout << "error in arguments\n";
	else
	{
		HANDLE h = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (h == INVALID_HANDLE_VALUE) print_error_message();
		else
		{
			HANDLE g = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (g == INVALID_HANDLE_VALUE)
			{
				print_error_message();
				CloseHandle(h);
			}
			else
			{
				int i = 0;
				unsigned long z, z1; 
				char a;
				ReadFile(h, &a, 1, &z, NULL);
				while (z != 0)
				{
					if (a >= 'a' && a <= 'z')
					{
						i++;
						WriteFile(g, &a, 1, &z1, NULL);
					}
					if (i > 20)
						break;
					else {
						ReadFile(h, &a, 1, &z, NULL);
					}
				}
			CloseHandle(h); 
			CloseHandle(g);
			}
			if(!MoveFile(argv[1], argv[3])) print_error_message();
		}
	}
	return 0;
}

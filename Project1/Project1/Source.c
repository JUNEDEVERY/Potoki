#include "Header.h"

#define PATH "DLLCode.dll"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	system("chcp 1251>nul");
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibraryA(PATH)) == NULL) return 1;
	MyFunctionCountProstNumber getCount = (MyFunctionCountProstNumber)GetProcAddress(hMyDLL, "GetCountProstNumber");
	int c = getCount(1, 10000);
	char* str1 = calloc(10, sizeof(char));
	_itoa(c, str1, 10);
	MessageBoxA(NULL, str1, "Колличество простых чисел", MB_OK);
	MyFunctionCountProstNumberThear getCountThear = (MyFunctionCountProstNumberThear)GetProcAddress(hMyDLL, "GetCountThert");
	int d = getCountThear(1, 10000, 5);
	char* str2 = calloc(10, sizeof(char));
	_itoa(d, str2, 10);
	MessageBoxA(NULL, str2, "Колличество простых чисел", MB_OK);
	FreeLibrary(hMyDLL);
	return 0;
}
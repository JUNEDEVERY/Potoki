#include "Header.h"

#define PATH "DLLCode.dll"
typedef res(_cdecl* MyFunctionCountProstNumber)(int, int);
typedef res(_cdecl* MyFunctionCountProstNumberThear)(int, int, int);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	system("chcp 1251>nul");
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibraryA(PATH)) == NULL) return 1;
	MyFunctionCountProstNumber getCount = (MyFunctionCountProstNumber)GetProcAddress(hMyDLL, "GetCountProstNumber");
	res r1 = getCount(1, 500000);
	char* str1 = calloc(10, sizeof(char));
	char* str2 = calloc(10, sizeof(char));
	char str3[5] = { ' ','з','а',' ' };
	_itoa(r1.count, str1, 10);
	_itoa(r1.time, str2, 10);
	LPWSTR l = strcat(str1, str3);
	l = strcat(l, str2);
	MessageBoxA(NULL, l, "Количество простых чисел", MB_OK);

	MyFunctionCountProstNumberThear getCountThear = (MyFunctionCountProstNumberThear)GetProcAddress(hMyDLL, "GetCountThert");
	res r2 = getCountThear(1, 500000,4);
	char* str4 = calloc(10, sizeof(char));
	char* str5 = calloc(10, sizeof(char));
	char str6[5] = { ' ','з','а',' ' };
	_itoa(r2.count, str4, 10);
	_itoa(r2.time, str5, 10);
	LPWSTR l2 = strcat(str4, str6);
	l2 = strcat(l2, str5);
	MessageBoxA(NULL, l2, "Колличество простых чисел в", MB_OK);
	FreeLibrary(hMyDLL);
	
	return 0;
}

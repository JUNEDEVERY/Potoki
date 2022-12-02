#include "Header.h"

#define PATHDLL "DLLCode.dll"
typedef res(_cdecl* MyFunctionCountProstNumber)(int, int);
typedef res(_cdecl* MyFunctionCountProstNumberThear)(int, int, int);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	system("chcp 1251>nul");
	HINSTANCE MyDLL;
	if (!(MyDLL = LoadLibraryA(PATHDLL))) {
		MessageBox(NULL, L"Произошла ошибка при открытии DLL библиотеки", L"Что-то не так", MB_OK);
	}
	
	MyFunctionCountProstNumber getCount = (MyFunctionCountProstNumber)GetProcAddress(MyDLL, "GetCountProstNumber");
	res r1 = getCount(1, 1000);
	char* str1 = calloc(10, sizeof(char));
	char* str2 = calloc(10, sizeof(char));
	char str3[5] = { ' ','з','а',' ' };
	_itoa(r1.count, str1, 10); // парсим в строку
	_itoa(r1.time, str2, 10);
	LPWSTR l = strcat(str1, str3);
	l = strcat(l, str2);	
	MessageBoxA(NULL, l, "Количество простых чисел", MB_OK);

	MyFunctionCountProstNumberThear getCountThear = (MyFunctionCountProstNumberThear)GetProcAddress(MyDLL, "GetCountThert");
	res r2 = getCountThear(1, 1000 ,4);
	char* str4 = calloc(10, sizeof(char));
	char* str5 = calloc(10, sizeof(char));
	char str6[5] = { ' ','з','а',' ' };
	_itoa(r2.count, str4, 10);
	_itoa(r2.time, str5, 10);
	LPWSTR l2 = strcat(str4, str6);
	l2 = strcat(l2, str5);
	MessageBoxA(NULL, l2, "Колличество простых чисел", MB_OK);
	FreeLibrary(MyDLL);
	
	return 0;
}

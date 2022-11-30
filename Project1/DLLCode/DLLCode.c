#include "..\Project1\Header.h"

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD dwReason,     // reason for calling function
	LPVOID ipReserved)  // reserved
{
	BOOL ballWentWell = TRUE;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.1
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

	if (ballWentWell)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CRITICAL_SECTION selection = { 0 };
int countProst;

int time;

BOOL GetProst(int n) // Определение простого числа
{
	if (n > 1)
	{
		for (int i = 2; i < n; i++)
		{
			if (n % i == 0)
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

__declspec(dllexport)res GetCountProstNumber(int a, int b) // Подсчет количества простых чисел
{
	int st = clock();
	int count = 0;
	for (int i = a; i <= b; i++)
	{
		if (GetProst(i) == TRUE)
		{
			count++;
		}
	}
	int end = clock();
	time = end - st;
	res r;
	r.time = time;
	r.count = count;
	return r;
}

DWORD WINAPI ThreadCountProstNumberThread1(int a[])
{
	int in = 0,b= a[0],b1= a[1];
	for (int i = b; i <= b1; i++)
	{
		if (GetProst(i) == TRUE)
		{
			EnterCriticalSection(&selection);
			countProst++;
			LeaveCriticalSection(&selection);
		}
	}
}

__declspec(dllexport)res GetCountThert(int a, int b, int c) // Функция которая определяет простые числа в несколько потоков
{
	int st = clock();
	countProst = 0;
	HANDLE* tThread = calloc(c, sizeof(HANDLE));
	InitializeCriticalSection(&selection);
	int v = 0;
	int p = (b / c)-1;
	for (int i = a; i <= b - p; i+=p+1)
	{
		int param[2];
		if (i + p >= b-1)
		{
			param[0] = i;
			param[1] = b;
		}
		else
		{
			param[0] = i;
			param[1] = i + p;
		}
		tThread[v] = CreateThread(NULL, 0, ThreadCountProstNumberThread1, param, 0, 0);
		Sleep(1);
		v++;
	}
	WaitForMultipleObjects(c, tThread, TRUE, INFINITE);
	DeleteCriticalSection(&selection);
	int end = clock();
	time = end - st;
	res r;
	r.time = time;
	r.count = countProst;
	return r;
}
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
		// Return FALSE to fail DLL load.
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

int GetCountProstNumber(int a, int b) // Подсчет количества простых чисел
{
	int count = 0;
	for (int i = a; i <= b; i++)
	{
		if (GetProst(i) == TRUE)
		{
			count++;
		}
	}
	return count;
}



//DWORD WINAPI ThreadCountProstNumber(LPVOID param)
//{
//	while (1)
//	{
//		if (i < end)
//		{
//			EnterCriticalSection(&selection);
//			if (GetProst(i) == TRUE)
//			{
//				countProst++;
//			}
//			i++;
//			LeaveCriticalSection(&selection);
//		}
//		else
//		{
//			break;
//		}
//	}
//}

DWORD WINAPI ThreadCountProstNumberThread1(int a[])
{
	for (int i = a[0]; i <= a[1]; i++)
	{
		if (GetProst(i) == TRUE)
		{
			EnterCriticalSection(&selection);
			countProst++;
			LeaveCriticalSection(&selection);
		}
	}
}

int GetCountThert(int a, int b, int c) // Функция которая определяет простые числа в несколько потоков
{
	int st_time = clock();
	countProst = 0;
	HANDLE* tThread = calloc(c, sizeof(HANDLE));
	
	/*InitializeCriticalSection(&selection);
	int st = clock();
 	for (j = 0; j < c; j++)
	{
		tThread[j] = CreateThread(NULL, 0, ThreadCountProstNumber, NULL, 0, 0);
	}
	int end = clock();
	WaitForMultipleObjects(c, tThread, TRUE, INFINITE);
	DeleteCriticalSection(&selection);
	int end_time = clock();
	time = end_time - st_time - (end - st);
	return countProst;
	*/
	InitializeCriticalSection(&selection);
	int v = 0;
	int p = (b - a) / c;
	int st = clock();
	for (int i = 1; i <= b - p; i+=p+1)
	{
		int param[2];
		if (i + p > b)
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
		Sleep(2);
		v++;
	}
	int end = clock();
	WaitForMultipleObjects(c, tThread, TRUE, INFINITE);
	DeleteCriticalSection(&selection);
	int end_time = clock();
	time = end_time - st_time - (end - st);
	return countProst;
}
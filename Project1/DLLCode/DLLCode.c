#include "..\Project1\Header.h"

BOOL WINAPI DllMain(HINSTANCE hlnstDll, DWORD dwReason, LPVOID IpReserved)
{
	BOOL bAllWentWell = TRUE; //  Т ВХОДА
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	if (bAllWentWell)
		return TRUE;
	else
		return FALSE;
}

CRITICAL_SECTION selection = { 0 };
int chisloProstyx;
int time; // в тактах

BOOL GetProst(int n) // простое число
{
	if (n > 1)
	{
		// в цикле перебираем числа от 2 до n - 1
		for (int i = 2; i < n; i++)
		{
			if (n % i == 0) // если n делится без остатка на i - возвращаем false (число не простое)
			
				return FALSE;
			
		}
		// если программа дошла до данного оператора, то возвращаем true (число простое) - проверка пройдена
		return TRUE;
	}
	// если программа дошла до данного оператора, то возвращаем true (число простое) - проверка пройдена
	else return FALSE;
		
	
}

__declspec(dllexport)res GetCountProstNumber(int a, int b) // Подсчет количества простых чисел
{
	int start = clock();
	int count = 0;
	for (int i = a; i <= b; i++)
	{
		if (GetProst(i) == TRUE)
		{
			count++;
		}
	}
	int end = clock();
	time = end - start;  // разница между конечным и начальным временем в тактах (сколько времени все выполнялось в тактах)
	res r;
	r.time = time;
	r.count = count;
	return r;
}

DWORD WINAPI PotolProstyxChisel(int a[])
{
	int in = 0,b= a[0],b1= a[1];
	for (int i = b; i <= b1; i++)
	{
		if (GetProst(i) == TRUE)
		{
			EnterCriticalSection(&selection); // к.с - доступ получает один поток и все процессы ожидают его завершения
			chisloProstyx++; // если процесс попытается обратиться, то процесс будет ждать лив
			LeaveCriticalSection(&selection);
		}
	}
}

__declspec(dllexport)res GetCountThert(int a, int b, int c) // простые числа в несколько потоков
{
	int st = clock();
	chisloProstyx = 0;
	HANDLE* tThread = calloc(c, sizeof(HANDLE));
	InitializeCriticalSection(&selection);
	int v = 0;
	int p = (b / c) - 1; //  определение шага
	for (int i = a; i <= b - p; i+=p+1)
	{
		int param[2];
		if (i + p >= b-1)             // текущее начало + шаг ( в последний поток ставим граничное значение b без шага)
		{
			param[0] = i;
			param[1] = b;
		}
		else
		{
			param[0] = i;
			param[1] = i + p;
		}
		tThread[v] = CreateThread(NULL, 0, PotolProstyxChisel, param, 0, 0);
		Sleep(1);
		v++;
	}
	WaitForMultipleObjects(c, tThread, TRUE, INFINITE);
	DeleteCriticalSection(&selection);
	int end = clock();
	time = end - st;
	res r;
	r.time = time;
	r.count = chisloProstyx;
	return r;
}
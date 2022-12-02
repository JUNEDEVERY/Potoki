#include "..\Project1\Header.h"

BOOL WINAPI DllMain(HINSTANCE hlnstDll, DWORD dwReason, LPVOID IpReserved)
{
	BOOL bAllWentWell = TRUE; //  � �����
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
int time; // � ������

BOOL GetProst(int n) // ������� �����
{
	if (n > 1)
	{
		// � ����� ���������� ����� �� 2 �� n - 1
		for (int i = 2; i < n; i++)
		{
			if (n % i == 0) // ���� n ������� ��� ������� �� i - ���������� false (����� �� �������)
			
				return FALSE;
			
		}
		// ���� ��������� ����� �� ������� ���������, �� ���������� true (����� �������) - �������� ��������
		return TRUE;
	}
	// ���� ��������� ����� �� ������� ���������, �� ���������� true (����� �������) - �������� ��������
	else return FALSE;
		
	
}

__declspec(dllexport)res GetCountProstNumber(int a, int b) // ������� ���������� ������� �����
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
	time = end - start;  // ������� ����� �������� � ��������� �������� � ������ (������� ������� ��� ����������� � ������)
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
			EnterCriticalSection(&selection); // �.� - ������ �������� ���� ����� � ��� �������� ������� ��� ����������
			chisloProstyx++; // ���� ������� ���������� ����������, �� ������� ����� ����� ���
			LeaveCriticalSection(&selection);
		}
	}
}

__declspec(dllexport)res GetCountThert(int a, int b, int c) // ������� ����� � ��������� �������
{
	int st = clock();
	chisloProstyx = 0;
	HANDLE* tThread = calloc(c, sizeof(HANDLE));
	InitializeCriticalSection(&selection);
	int v = 0;
	int p = (b / c) - 1; //  ����������� ����
	for (int i = a; i <= b - p; i+=p+1)
	{
		int param[2];
		if (i + p >= b-1)             // ������� ������ + ��� ( � ��������� ����� ������ ��������� �������� b ��� ����)
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
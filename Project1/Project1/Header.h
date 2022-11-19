#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <Windows.h>

__declspec(dllexport) int GetCountProstNumber(int, int);
__declspec(dllexport) int GetCountThert(int, int, int);

typedef int(_cdecl* MyFunctionCountProstNumber)(int, int);
typedef int(_cdecl* MyFunctionCountProstNumberThear)(int, int, int);
#include "Win32Header.h"

void Sys_InitTimer()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&win32_vars.frequency);
}

uint64_t Sys_GetTime()
{
	uint64_t time;
	QueryPerformanceCounter((LARGE_INTEGER*)&time);
	return time;
}

uint64_t Sys_GetFrequency()
{
	return win32_vars.frequency;
}
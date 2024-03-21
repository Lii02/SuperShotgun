#include "Win32Header.h"
#include <lilib/Assert.h>

void Sys_UseThread(int index, DWORD(*fun_ptr)(LPVOID), void* param)
{
	LILIB_ASSERT(index >= 0 && index <= WIN32_THREAD_COUNT, "Thread index is out of bounds!");
	win32_vars.threads[index] = CreateThread(0, 0, fun_ptr, param, 0, &win32_vars.thread_ids[index]);
	win32_vars.thread_status[index] = true;
}

void Sys_CloseThread(int index)
{
	LILIB_ASSERT(index >= 0 && index <= WIN32_THREAD_COUNT, "Thread index is out of bounds!");
	CloseHandle(win32_vars.threads[index]);
	win32_vars.thread_status[index] = false;
}

DWORD Sys_GetCurrentThreadID()
{
	return GetCurrentThreadId();
}

bool Sys_IsThreadActive(int index)
{
	return win32_vars.thread_status[index];
}

void Sys_JoinThread(int index)
{
	WaitForSingleObject(win32_vars.threads[index], 0);
	Sys_CloseThread(index);
}
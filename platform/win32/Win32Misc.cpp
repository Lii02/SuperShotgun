#include "Win32Header.h"

void Sys_LockMemory(libyte* block, size_t size)
{
	VirtualLock(block, size);
}

void Sys_UnlockMemory(libyte* block, size_t size)
{
	VirtualUnlock(block, size);
}

cstring Sys_GetUserName()
{
	DWORD length = (DWORD)strlen(win32_vars.username);
	GetUserNameA(win32_vars.username, &length);
	return win32_vars.username;
}
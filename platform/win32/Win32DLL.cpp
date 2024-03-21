#include "Win32Header.h"

SysDLL Sys_LoadDLL(cstring name)
{
	return LoadLibraryA(name);
}

SysDLLFunction Sys_LoadFunction(SysDLL dll, cstring name)
{
	return GetProcAddress(dll, name);
}

void Sys_FreeDLL(SysDLL dll)
{
	FreeLibrary(dll);
}
#include "Debug.h"
#include <platform/win32/Win32Header.h>

void Debug::Log(liString message)
{
	Sys_SetFG(Win32ConsoleColor::COLOR_WHITE);
	printf("%s\n", message.c_str());
	Sys_ResetColors();
}

void Debug::LogWarning(liString message)
{
	Sys_SetFG(Win32ConsoleColor::COLOR_YELLOW);
	printf("%s\n", message.c_str());
	Sys_ResetColors();
}

void Debug::LogError(liString message)
{
	Sys_SetFG(Win32ConsoleColor::COLOR_RED);
	printf("%s\n", message.c_str());
	Sys_ResetColors();
}
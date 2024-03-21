#include "Win32Header.h"

void Sys_SetupConsole()
{
	win32_vars.console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	win32_vars.console_window = GetConsoleWindow();
	Sys_ResetColors();
}

void Sys_SetFG(liWin32ConsoleColor fg)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(win32_vars.console_handle, &info);
	SetConsoleTextAttribute(win32_vars.console_handle, info.wAttributes & 0xF0 | (WORD)fg);
	win32_vars.fg = fg;
}

void Sys_SetBG(liWin32ConsoleColor bg)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(win32_vars.console_handle, &info);
	SetConsoleTextAttribute(win32_vars.console_handle, info.wAttributes & 0x0F | (WORD)bg << 4);
	win32_vars.bg = bg;
}

void Sys_ResetColors()
{
	Sys_SetFG(liWin32ConsoleColor::COLOR_GRAY);
	Sys_SetBG(liWin32ConsoleColor::COLOR_BLACK);
}
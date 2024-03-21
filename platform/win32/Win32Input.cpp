#include "Win32Header.h"

short Sys_GetMouseX()
{
	return win32_vars.mousex;
}

short Sys_GetMouseY()
{
	return win32_vars.mousey;
}

bool Sys_IsKeyDown(ubyte key)
{
	return win32_vars.keys[key];
}

bool Sys_IsMButtonDown(ubyte mbutton)
{
	return win32_vars.mbuttons[mbutton];
}

void Sys_ShowCursor()
{
	ShowCursor(true);
}

void Sys_HideCursor()
{
	ShowCursor(false);
}

void Sys_LockCursor()
{
	RECT rect;
	GetWindowRect(win32_vars.handle, &rect);
	ClipCursor(&rect);
}

void Sys_FreeCursor()
{
	ClipCursor(NULL);
}
#ifndef WIN32HEADER_H
#define WIN32HEADER_H
#include <Windows.h>
#include "lilib/EngineDefs.h"

enum liWin32ConsoleColor : ubyte {
	COLOR_BLACK = 0,
	COLOR_DARK_BLUE = FOREGROUND_BLUE,
	COLOR_DARK_GREEN = FOREGROUND_GREEN,
	COLOR_DARK_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
	COLOR_DARK_RED = FOREGROUND_RED,
	COLOR_DARK_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
	COLOR_DARK_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
	COLOR_GRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	COLOR_DARK_GRAY = FOREGROUND_INTENSITY,
	COLOR_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	COLOR_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	COLOR_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	COLOR_RED = FOREGROUND_RED | FOREGROUND_INTENSITY,
	COLOR_MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	COLOR_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	COLOR_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
};

#define WIN32_THREAD_COUNT 4

typedef HMODULE SysDLL;
typedef HANDLE SysDLLFunction;

struct liWin32Vars {
	HWND handle;
	HINSTANCE instance;
	bool running;
	int width, height;
	HDC dc;
	cstring title;
	HANDLE console_handle;
	HWND console_window;

	// OpenGL
	HGLRC gl;

	// Misc windows variables
	char username[0xFF];

	// Keyboard, Mouse, and gamepad input data
	bool keys[0xFF];
	bool mbuttons[0xA];
	short mousex, mousey;

	// Timer
	uint64_t frequency;

	// Console
	liWin32ConsoleColor fg, bg;

	// Threads
	HANDLE threads[WIN32_THREAD_COUNT];
	DWORD thread_ids[WIN32_THREAD_COUNT];
	bool thread_status[WIN32_THREAD_COUNT];
};

// Win32Window
void Sys_Setup(cstring title, int width, int height);
void Sys_StartWindow();
void Sys_CloseWindow();
void Sys_PollWindow();
bool Sys_IsRunning();
void Sys_SetTitle(cstring new_title);
void Sys_ResetInput();
float Sys_GetAspectRatio();
void Sys_SetDimensions(int new_width, int new_height);
int Sys_GetWidth();
int Sys_GetHeight();

// Win32Misc
void Sys_LockMemory(libyte* block, size_t size);
void Sys_UnlockMemory(libyte* block, size_t size);
cstring Sys_GetUserName();

// Win32Timer
void Sys_InitTimer();
uint64_t Sys_GetTime();
uint64_t Sys_GetFrequency();

// Win32GL
void Sys_StartupGL();
void Sys_ShutdownGL();

// Win32Console
void Sys_SetupConsole();
void Sys_SetFG(liWin32ConsoleColor fg);
void Sys_SetBG(liWin32ConsoleColor bg);
void Sys_ResetColors();

// Win32IO
void Sys_CreateFolder(cstring path);
bool Sys_FolderExists(cstring name);

// Win32Thread
void Sys_UseThread(int index, DWORD(*fun_ptr)(LPVOID), void* param);
void Sys_CloseThread(int index);
DWORD Sys_GetCurrentThreadID();
bool Sys_IsThreadActive(int index);
void Sys_JoinThread(int index);

// Win32Input
short Sys_GetMouseX();
short Sys_GetMouseY();
bool Sys_IsKeyDown(ubyte key);
bool Sys_IsMButtonDown(ubyte mbutton);
void Sys_ShowCursor();
void Sys_HideCursor();
void Sys_LockCursor();
void Sys_FreeCursor();

// Win32DLL
SysDLL Sys_LoadDLL(cstring name);
SysDLLFunction Sys_LoadFunction(SysDLL dll, cstring name);
void Sys_FreeDLL(SysDLL dll);

// Win32Gamepad

extern liWin32Vars win32_vars;

#endif
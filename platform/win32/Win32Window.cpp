#include "Win32Header.h"

liWin32Vars win32_vars;

LRESULT CALLBACK WindowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_MOUSEMOVE: {
		short x = lParam & 0xFFFF;
		short y = (lParam >> 16) & 0xFFFF;
		short ix = *(short*)&x;
		short iy = *(short*)&y;
		win32_vars.mousex = ix;
		win32_vars.mousey = iy;
		return 0;
	}
	case WM_KEYDOWN: {
		win32_vars.keys[wParam] = true;
		return 0;
	}
	case WM_SYSKEYDOWN: {
		win32_vars.keys[wParam] = true;
		return 0;
	}
	case WM_KEYUP: {
		win32_vars.keys[wParam] = false;
		return 0;
	}
	case WM_SYSKEYUP: {
		win32_vars.keys[wParam] = false;
		return 0;
	}
	case WM_LBUTTONDOWN: {
		win32_vars.mbuttons[0] = true;
		return 0;
	}
	case WM_LBUTTONUP: {
		win32_vars.mbuttons[0] = false;
		return 0;
	}
	case WM_RBUTTONDOWN: {
		win32_vars.mbuttons[1] = true;
		return 0;
	}
	case WM_RBUTTONUP: {
		win32_vars.mbuttons[1] = false;
		return 0;
	}
	case WM_MBUTTONDOWN: {
		win32_vars.mbuttons[2] = true;
		return 0;
	}
	case WM_MBUTTONUP: {
		win32_vars.mbuttons[2] = false;
		return 0;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(handle, message, wParam, lParam);
}

void Sys_Setup(cstring title, int width, int height)
{
	Sys_ResetInput();
	Sys_InitTimer();
	memset(win32_vars.username, ' ', 0xFF);
	win32_vars.instance = GetModuleHandle(NULL);
	win32_vars.title = title;
	win32_vars.width = width;
	win32_vars.height = height;
}

void Sys_StartWindow()
{
	WNDCLASSEX wc = { 0 };
	wc.style = 0;
	wc.hInstance = win32_vars.instance;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcedure;
	wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wc.lpszClassName = L"LiWindowClass";
	RegisterClassEx(&wc);

	DWORD style = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX;
	DWORD exsyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	win32_vars.handle = CreateWindowEx(exsyle, wc.lpszClassName, L"Title", style, CW_USEDEFAULT, CW_USEDEFAULT, win32_vars.width, win32_vars.height, 0, 0, win32_vars.instance, 0);
	win32_vars.dc = GetDC(win32_vars.handle);
	win32_vars.running = true;
	ShowWindow(win32_vars.handle, SW_RESTORE);

	Sys_SetTitle(win32_vars.title);
}

void Sys_CloseWindow()
{
	ReleaseDC(win32_vars.handle, win32_vars.dc);
	CloseWindow(win32_vars.handle);
}

void Sys_PollWindow()
{
	SwapBuffers(win32_vars.dc);
	MSG msg;
	if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			win32_vars.running = false;
	} else {
		win32_vars.running = true;
	}
}

bool Sys_IsRunning()
{
	return win32_vars.running;
}

void Sys_SetTitle(cstring new_title)
{
	win32_vars.title = new_title;
	SetWindowTextA(win32_vars.handle, new_title);
}

void Sys_ResetInput()
{
	memset(&win32_vars.keys, 0, 0xFF);
	memset(&win32_vars.mbuttons, 0, 0xA);
	win32_vars.mousex = 0;
	win32_vars.mousey = 0;
}

float Sys_GetAspectRatio()
{
	return (float)win32_vars.width / (float)win32_vars.height;
}

void Sys_SetDimensions(int new_width, int new_height)
{
	win32_vars.width = new_width;
	win32_vars.height = new_height;
	SetWindowPos(win32_vars.handle, HWND_TOPMOST, 0, 0, new_width, new_height, SWP_NOREPOSITION | SWP_NOZORDER | SWP_SHOWWINDOW);
}

int Sys_GetWidth()
{
	return win32_vars.width;
}

int Sys_GetHeight()
{
	return win32_vars.height;
}
#include "Win32Header.h"
#include <gl/GL.h>

void Sys_StartupGL()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	int pf = 0;
	pf = ChoosePixelFormat(win32_vars.dc, &pfd);
	SetPixelFormat(win32_vars.dc, pf, &pfd);
	win32_vars.gl = wglCreateContext(win32_vars.dc);
	wglMakeCurrent(win32_vars.dc, win32_vars.gl);
}

void Sys_ShutdownGL()
{
	wglDeleteContext(win32_vars.gl);
}
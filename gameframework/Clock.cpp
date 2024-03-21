#include "Clock.h"
#ifdef ENGINE_WINDOWS
#include <platform/win32/Win32Header.h>
#endif

void liClock::Start()
{
	last_frame = (float)Sys_GetTime();
}

float liClock::DeltaTime()
{
	float current_frame = (float)Sys_GetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;
	return delta_time / Sys_GetFrequency();
}
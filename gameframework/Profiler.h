#ifndef FRAMEWORK_PROFILER_H
#define FRAMEWORK_PROFILER_H
#include <lilib/EngineDefs.h>
#include <lilib/LiString.h>
#include <lilib/Stack.h>
#include "Clock.h"

struct profiler_item_t {
	liString name;
	float32 time;
	liString guid;
	liClock clock;
};

class liProfiler {
private:
public:
	static liList<profiler_item_t>* items;

	static void Startup();
	static void Shutdown();
	static void StartFunction(liString tag);
	static void EndFunction();
	static void ResetProfiler();
	static profiler_item_t* GetByIndex(size_t index);
	static profiler_item_t* GetByName(liString name, int counter = 0);
	static float32 GetAverage(liString name);
};

#endif
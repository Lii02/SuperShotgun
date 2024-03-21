#include "Profiler.h"
#include <lilib/GUID.h>

liList<profiler_item_t>* liProfiler::items = nullptr;

void liProfiler::Startup()
{
	items = new liList<profiler_item_t>();
}

void liProfiler::Shutdown()
{
	ResetProfiler();
	delete items;
}

void liProfiler::StartFunction(liString tag)
{
	profiler_item_t item;
	item.name = tag;
	item.clock.Start();
	item.guid = LiLib_GenerateGUID();
	items->Push(item);
}

void liProfiler::EndFunction()
{
	items->Pop();
	profiler_item_t* item = &(*items)[items->Size()];
	item->time = item->clock.DeltaTime() * 1000.0f;
}

void liProfiler::ResetProfiler()
{
	items->Clear();
}

profiler_item_t* liProfiler::GetByIndex(size_t index)
{
	return &items->At(index);
}

profiler_item_t* liProfiler::GetByName(liString name, int counter)
{
	for (size_t i = counter; i < items->Size(); i++) {
		if (items->At(i).name == name)
			return &items->At(i);
	}
}

float32 liProfiler::GetAverage(liString name)
{
	int counter = 0;
	float32 average = 0;
	auto item = GetByName(name, counter);
	while (item) {
		average += item->time;
		counter++;
	}
	average /= counter;
	return average;
}
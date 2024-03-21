#include "Memory.h"

liMemory* liMemory::Instance = nullptr;

liMemory::liMemory()
{
	ResetUsage();
}

liMemory::~liMemory()
{
	ResetUsage();
}

void liMemory::ResetUsage()
{
	this->usage = 0;
}

void* liMemory::Allocate(size_t size)
{
	size_t* mem = (size_t*)malloc(size + sizeof(size_t));
	mem[0] = size;
	this->usage += size;
	return (void*)(&mem[1]);
}

void liMemory::Free(void* memory)
{
	if (!memory)
		return;

	size_t* mem = (size_t*)memory;
	this->usage -= mem[-1];
	void* ptr = (void*)(&mem[-1]);
	free(ptr);
}

void* operator new(size_t size) noexcept
{
	return liMemory::Instance->Allocate(size);
}

void operator delete(void* memory) noexcept
{
	liMemory::Instance->Free(memory);
}

void LiLib_InitMemory()
{
	liMemory::Instance = (liMemory*)malloc(sizeof(liMemory));
	liMemory::Instance->ResetUsage();
}

void LiLib_ShutdownMemory()
{
	free(liMemory::Instance);
}
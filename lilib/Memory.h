#ifndef LILIB_MEMORY_H
#define LILIB_MEMORY_H
#include "EngineDefs.h"

class liMemory {
private:
	unsigned long long usage;
public:
	static liMemory* Instance;

	liMemory();
	~liMemory();

	void ResetUsage();
	inline unsigned long long GetUsage() const { return usage; }

	void* Allocate(size_t size);
	void Free(void* memory);

	template <typename Type>
	Type* Resize(Type* data, size_t new_size, size_t old_size);
};

void* operator new(size_t size) noexcept;
void operator delete(void* memory) noexcept;

template<typename Type>
inline Type* liMemory::Resize(Type* data, size_t new_size, size_t old_size)
{
	Type* new_arr = new Type[new_size];
	memcpy(new_arr, data, old_size * sizeof(Type));
	if(data)
		delete[] data;
	return new_arr;
}

void LiLib_InitMemory();
void LiLib_ShutdownMemory();

#endif
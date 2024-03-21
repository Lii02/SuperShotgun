#ifndef LILIB_STACK_H
#define LILIB_STACK_H
#include "Allocator.h"

template <typename Type>
class liStack : liAllocator<Type> {
public:
	Type* stackptr;
	size_t size;
public:
	liStack(size_t size = 1);
	liStack(const liStack& from);
	liStack& operator=(const liStack& from);

	Type* GetPtr();
	void Pop();
	void Push(const Type& val);
	size_t Size() const;
	size_t MemoryUsed() const;
	void Clear();
};

template<typename Type>
inline liStack<Type>::liStack(size_t size)
{
	Initialize();
	Resize(size);
	this->size = 0;
	stackptr = &data[0];
}

template<typename Type>
inline liStack<Type>::liStack(const liStack<Type>& from)
{
	*this = from;
}

template<typename Type>
inline liStack<Type>& liStack<Type>::operator=(const liStack<Type>& from)
{
	return *this;
}

template<typename Type>
inline Type* liStack<Type>::GetPtr()
{
	return stackptr;
}

template<typename Type>
inline void liStack<Type>::Pop()
{
	size--;
	stackptr--;
}

template<typename Type>
inline void liStack<Type>::Push(const Type& val)
{
	if (size >= capacity)
		Resize();
	*stackptr++ = val;
	size++;
}

template<typename Type>
inline size_t liStack<Type>::Size() const
{
	return size;
}

template<typename Type>
inline size_t liStack<Type>::MemoryUsed() const
{
	return Allocated() + sizeof(liStack<Type>);
}

template<typename Type>
inline void liStack<Type>::Clear()
{
	this->size = 0;
	this->stackptr = &data[0];
}

#endif
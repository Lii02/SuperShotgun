#ifndef LILIB_LIST_H
#define LILIB_LIST_H
#include "Allocator.h"

template <typename Type>
class liList : public liAllocator<Type> {
protected:
	size_t size;
public:
	virtual Iterator Begin() override {
		Iterator it;
		it.SetCurrent(&data[0]);
		return it;
	}

	virtual Iterator End() override {
		Iterator it;
		it.SetCurrent(&data[size]);
		return it;
	}

	liList();
	liList(size_t start_size);
	liList(const liList& from);
	liList& operator=(const liList& from);
	
	liList& Copy(const liList& from, size_t extra = 0);
	void Initialize();
	inline void Push(Type value);
	inline void Pop(unsigned int amount = 1);
	const Type& Front();
	const Type& Back();
	void SetSize(size_t new_size);
	inline size_t Size() const;
	inline size_t MemoryUsed() const;
	inline void DeleteDataPointers();

	Iterator& Insert(Iterator iter, Type data) {
		if (size == 0) {
			Push(data);
			iter = End();
		} else if (iter != End()) {
			Push(data);
			iter = End();
		} else {
			liList arr;
			for (auto it = Begin(); it != End(); it++) {
				if (*it == *iter) {
					arr.Push(data);
					iter = it;
				}
				arr.Push(*it);
			}
			this->Copy(arr);
		}
		return iter;
	}

	Iterator& Erase(Iterator iter) {
		if (size == 0) {
			iter = Begin();
		} else {
			liList arr;
			for (auto it = Begin(); it != End(); it++) {
				arr.Push(*it);
				if (*it == *iter) {
					arr.Pop();
					*iter = *it;
				}
			}
			this->Copy(arr);
		}
		return iter;
	}
};

template<typename Type>
inline liList<Type>::liList()
{
	Initialize();
}

template<typename Type>
inline liList<Type>::liList(size_t start_size)
{
	Initialize();
	Resize(start_size);
	SetSize(start_size);
}

template<typename Type>
inline liList<Type>::liList(const liList& from)
{
	this->data = NULL;
	*this = from;
}

template<typename Type>
inline liList<Type>& liList<Type>::operator=(const liList<Type>& from)
{
	return Copy(from);
}

template<typename Type>
inline liList<Type>& liList<Type>::Copy(const liList<Type>& from, size_t extra)
{
	Clear();
	size_t new_capacity = from.Size() + extra;
	if(new_capacity > 0)
		Resize(new_capacity);
	for (size_t i = 0; i < from.Size(); i++) {
		Push(from[i]);
	}
	this->SetSize(from.Size());
	return *this;
}

template<typename Type>
inline void liList<Type>::Initialize()
{
	this->size = 0;
	liAllocator<Type>::Initialize();
}

template<typename Type>
inline void liList<Type>::Push(Type value)
{
	if (size >= capacity)
		Resize();
	this->data[size++] = value;
}

template<typename Type>
inline void liList<Type>::Pop(unsigned int amount)
{
	this->size -= amount;
}

template<typename Type>
inline const Type& liList<Type>::Front()
{
	return data[0];
}

template<typename Type>
inline const Type& liList<Type>::Back()
{
	return data[size];
}

template<typename Type>
inline void liList<Type>::SetSize(size_t new_size)
{
	this->size = new_size;
}

template<typename Type>
inline size_t liList<Type>::Size() const
{
	return size;
}

template<typename Type>
inline size_t liList<Type>::MemoryUsed() const
{
	return Allocated() + sizeof(liList<Type>);
}

template<typename Type>
inline void liList<Type>::DeleteDataPointers()
{
	for (size_t i = 0; i < Size(); i++)
		delete data[i];
}

#endif
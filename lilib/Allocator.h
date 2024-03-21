#ifndef LILIB_ALLOCATOR_H
#define LILIB_ALLOCATOR_H
#include "EngineDefs.h"
#include "Memory.h"

template <typename Type>
class liAllocator {
protected:
	Type* data;
	size_t capacity;
public:
	class Iterator {
	private:
		Type* current;
	public:
		void SetCurrent(Type* current) {
			this->current = current;
		}

		Iterator& operator++() {
			current++;
			return *this;
		}

		Iterator& operator++(int) {
			Iterator& new_it = *this;
			current++;
			return new_it;
		}

		Iterator& operator+=(int i) {
			current += i;
			return *this;
		}

		Iterator operator+(int i) {
			Iterator it = *this;
			it += i;
			return it;
		}

		Iterator& operator--() {
			current--;
			return *this;
		}

		Iterator& operator--(int) {
			Iterator& new_it = *this;
			current--;
			return new_it;
		}

		Iterator& operator-=(int i) {
			current -= i;
			return *this;
		}

		Iterator operator-(int i) {
			Iterator it = *this;
			it -= i;
			return it;
		}

		Type& operator*() {
			return *current;
		}

		bool operator!=(Iterator right) {
			return current != right.current;
		}
	};
	virtual Iterator Begin() = 0;
	virtual Iterator End() = 0;

public:
	virtual ~liAllocator();
	void Clear();
	virtual void Initialize();
	void FreeData();
	void Resize(size_t new_capacity = 0);
	const Type& operator[](int index) const;
	Type& operator[](int index);
	inline Type& At(int index);
	inline size_t Capacity() const;
	inline size_t Allocated() const;
};

template<typename Type>
inline liAllocator<Type>::~liAllocator()
{
	FreeData();
}

template<typename Type>
inline void liAllocator<Type>::Clear()
{
	FreeData();
	Initialize();
}

template<typename Type>
inline void liAllocator<Type>::Initialize()
{
	this->capacity = 0;
	Resize();
}

template<typename Type>
inline void liAllocator<Type>::FreeData()
{
	if (data)
		delete[] data;
	this->data = NULL;
}

template<typename Type>
inline void liAllocator<Type>::Resize(size_t new_capacity)
{
	if (capacity == 0) {
		this->capacity = 1;
		this->data = new Type[capacity];
	} else if (new_capacity == 0) {
		data = liMemory::Instance->Resize<Type>(data, capacity * 2, capacity);
		capacity *= 2;
	} else if (new_capacity > capacity) {
		data = liMemory::Instance->Resize<Type>(data, new_capacity, capacity);
		this->capacity = new_capacity;
	}
}

template<typename Type>
inline const Type& liAllocator<Type>::operator[](int index) const
{
	return data[index];
}

template<typename Type>
inline Type& liAllocator<Type>::operator[](int index)
{
	return data[index];
}

template<typename Type>
inline Type& liAllocator<Type>::At(int index)
{
	return data[index];
}

template<typename Type>
inline size_t liAllocator<Type>::Capacity() const
{
	return capacity;
}

template<typename Type>
inline size_t liAllocator<Type>::Allocated() const
{
	return capacity * sizeof(Type);
}

#endif
#ifndef LILIB_DICTIONARY_H
#define LILIB_DICTIONARY_H
#include "Memory.h"
#include "Pair.h"

template <typename K, typename V>
class liDictionary {
private:
	size_t capacity, size;
	liPair<K, V>* data;
public:
	liDictionary();
	~liDictionary();
	liDictionary(const liDictionary& from);
	liDictionary& operator=(const liDictionary& from);

	liDictionary& Copy(const liDictionary& from);
	void Clear();
	void Initialize();
	void FreeData();
	void Resize(size_t new_capacity = 0);
	inline liPair<K, V>& At(int index);
	inline size_t Capacity() const;
	inline size_t Allocated() const;
	inline size_t Size() const;
	void Push(K key, V value);
	void Pop();
};

template<typename K, typename V>
inline liDictionary<K, V>::liDictionary()
{
	Initialize();
}

template<typename K, typename V>
inline liDictionary<K, V>::~liDictionary()
{
	FreeData();
}

template<typename K, typename V>
inline liDictionary<K, V>::liDictionary(const liDictionary& from)
{
	*this = from;
}

template<typename K, typename V>
inline liDictionary<K, V>& liDictionary<K, V>::operator=(const liDictionary& from)
{
	return Copy(from);
}

template<typename K, typename V>
inline liDictionary<K, V>& liDictionary<K, V>::Copy(const liDictionary& from)
{
	Clear();
	size_t new_capacity = from.Size();
	if (new_capacity > 0)
		Resize(new_capacity);
	for (size_t i = 0; i < from.Size(); i++) {
		Push(from[i]);
	}
	this->size = from.size;
	return *this;
}

template<typename K, typename V>
inline void liDictionary<K, V>::Clear()
{
	FreeData();
	Initialize();
}

template<typename K, typename V>
inline void liDictionary<K, V>::Initialize()
{
	this->capacity = 0;
	this->size = 0;
	Resize();
}

template<typename K, typename V>
inline void liDictionary<K, V>::FreeData()
{
	if (data)
		delete[] data;
	this->data = NULL;
}

template<typename K, typename V>
inline void liDictionary<K, V>::Resize(size_t new_capacity)
{
	if (capacity == 0) {
		this->capacity = 1;
		this->data = new liPair<K, V>[capacity];
	} else if (new_capacity == 0) {
		data = liMemory::Instance->Resize<liPair<K, V>>(data, capacity * 2, capacity);
		capacity *= 2;
	} else if (new_capacity > capacity) {
		data = liMemory::Instance->Resize<liPair<K, V>>(data, new_capacity, capacity);
		this->capacity = new_capacity;
	}
}

template<typename K, typename V>
inline liPair<K, V>& liDictionary<K, V>::At(int index)
{
	return data[index];
}

template<typename K, typename V>
inline size_t liDictionary<K, V>::Capacity() const
{
	return capacity;
}

template<typename K, typename V>
inline size_t liDictionary<K, V>::Allocated() const
{
	return capacity * sizeof(liPair<K, V>);
}

template<typename K, typename V>
inline size_t liDictionary<K, V>::Size() const
{
	return size;
}

template<typename K, typename V>
inline void liDictionary<K, V>::Push(K key, V value)
{
	if (size >= capacity)
		Resize();
	this->data[size++] = liPair<K, V>(key, value);
}

template<typename K, typename V>
inline void liDictionary<K, V>::Pop()
{
	this->size--;
}

#endif
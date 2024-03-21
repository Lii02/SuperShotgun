#ifndef LILIB_UNIQUE_H
#define LILIB_UNIQUE_H

template <typename Type>
class liUnique {
private:
	Type* ptr;
public:
	liUnique(Type* ptr);
	~liUnique();
	
	void Free();
	Type* operator->();
	Type& operator*();
};

template<typename Type>
inline liUnique<Type>::liUnique(Type* ptr)
{
	this->ptr = ptr;
}

template<typename Type>
inline liUnique<Type>::~liUnique()
{
	Free();
}

template<typename Type>
inline void liUnique<Type>::Free()
{
	delete ptr;
}

template<typename Type>
inline Type* liUnique<Type>::operator->()
{
	return ptr;
}

template<typename Type>
inline Type& liUnique<Type>::operator*()
{
	return *ptr;
}

#endif
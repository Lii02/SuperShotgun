#ifndef VECTORS_H
#define VECTORS_H
#include "../EngineDefs.h"
#include <math.h>

template<typename T>
class liVector2Generic {
public:
	T x = 0, y = 0;

	liVector2Generic() = default;
	liVector2Generic(T x, T y);
	float Length() const;
	liVector2Generic<T> Normalize();
	T* ToPtr();
	const T* ToPtr() const;
	void Set(T x, T y);
	T& operator[](int index);
	const T& operator[](int index) const;

	liVector2Generic operator-();
	liVector2Generic operator-(liVector2Generic right);
	liVector2Generic operator-=(liVector2Generic right);
	liVector2Generic operator+(liVector2Generic right);
	liVector2Generic operator+=(liVector2Generic right);
	liVector2Generic operator/(liVector2Generic right);
	liVector2Generic operator/=(liVector2Generic right);
	liVector2Generic operator*(liVector2Generic right);
	liVector2Generic operator*=(liVector2Generic right);
};

template<typename T>
inline liVector2Generic<T>::liVector2Generic(T x, T y)
{
	Set(x, y);
}

template<typename T>
inline float liVector2Generic<T>::Length() const
{
	return sqrtf(x * x + y * y);
}

template<typename T>
inline liVector2Generic<T> liVector2Generic<T>::Normalize()
{
	float l = Length();
	this->x /= l;
	this->y /= l;
	return *this;
}

template<typename T>
inline T* liVector2Generic<T>::ToPtr()
{
	return &x;
}

template<typename T>
inline const T* liVector2Generic<T>::ToPtr() const
{
	return (const T*)&x;
}

template<typename T>
inline void liVector2Generic<T>::Set(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<typename T>
inline T& liVector2Generic<T>::operator[](int index)
{
	return ToPtr()[index];
}

template<typename T>
inline const T& liVector2Generic<T>::operator[](int index) const
{
	return ToPtr()[index];
}

template<typename T>
inline liVector2Generic<T> liVector2Generic<T>::operator-()
{
	return liVector2Generic(-x, -y);
}

template<typename T>
inline liVector2Generic<T> liVector2Generic<T>::operator-(liVector2Generic right)
{
	return liVector2Generic(x - right.x, y - right.y);
}

template<typename T>
inline liVector2Generic<T> liVector2Generic<T>::operator-=(liVector2Generic right)
{
	*this = *this - right;
	return *this;
}

template<typename T>
inline liVector2Generic<T> liVector2Generic<T>::operator+(liVector2Generic right)
{
	return liVector2Generic(x + right.x, y + right.y);
}

template<typename T>
inline liVector2Generic<T> liVector2Generic<T>::operator+=(liVector2Generic right)
{
	*this = *this + right;
	return *this;
}

template<typename T>
inline liVector2Generic<T> liVector2Generic<T>::operator/(liVector2Generic right)
{
	return liVector2Generic(x / right.x, y / right.y);
}

template<typename T>
inline liVector2Generic<T> liVector2Generic<T>::operator/=(liVector2Generic right)
{
	*this = *this / right;
	return *this;
}

template<typename T>
inline liVector2Generic<T> liVector2Generic<T>::operator*(liVector2Generic right)
{
	return liVector2Generic(x * right.x, y * right.y);
}

template<typename T>
inline liVector2Generic<T> liVector2Generic<T>::operator*=(liVector2Generic right)
{
	*this = *this * right;
	return *this;
}

template<typename T>
class liVector3Generic {
public:
	T x = 0, y = 0, z = 0;

	liVector3Generic() = default;
	liVector3Generic(T x, T y, T z);
	float Length() const;
	liVector3Generic<T> Normalize();
	T* ToPtr();
	const T* ToPtr() const;
	void Set(T x, T y, T z);
	T& operator[](int index);
	const T& operator[](int index) const;

	liVector3Generic operator-();
	liVector3Generic operator-(liVector3Generic right);
	liVector3Generic operator-=(liVector3Generic right);
	liVector3Generic operator+(liVector3Generic right);
	liVector3Generic operator+=(liVector3Generic right);
	liVector3Generic operator/(liVector3Generic right);
	liVector3Generic operator/=(liVector3Generic right);
	liVector3Generic operator*(liVector3Generic right);
	liVector3Generic operator*=(liVector3Generic right);
};

template<typename T>
inline liVector3Generic<T>::liVector3Generic(T x, T y, T z)
{
	Set(x, y, z);
}

template<typename T>
inline float liVector3Generic<T>::Length() const
{
	return sqrtf(x * x + y * y + z * z);
}

template<typename T>
inline liVector3Generic<T> liVector3Generic<T>::Normalize()
{
	float l = Length();
	this->x /= l;
	this->y /= l;
	this->z /= l;
	return *this;
}

template<typename T>
inline T* liVector3Generic<T>::ToPtr()
{
	return &x;
}

template<typename T>
inline const T* liVector3Generic<T>::ToPtr() const
{
	return (const T*)&x;
}

template<typename T>
inline void liVector3Generic<T>::Set(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<typename T>
inline T& liVector3Generic<T>::operator[](int index)
{
	return ToPtr[index];
}

template<typename T>
inline const T& liVector3Generic<T>::operator[](int index) const
{
	return ToPtr[index];
}

template<typename T>
inline liVector3Generic<T> liVector3Generic<T>::operator-()
{
	return liVector3Generic(-x, -y, -z);
}

template<typename T>
inline liVector3Generic<T> liVector3Generic<T>::operator-(liVector3Generic right)
{
	return liVector3Generic(x - right.x, y - right.y, z - right.z);
}

template<typename T>
inline liVector3Generic<T> liVector3Generic<T>::operator-=(liVector3Generic right)
{
	*this = *this - right;
	return *this;
}

template<typename T>
inline liVector3Generic<T> liVector3Generic<T>::operator+(liVector3Generic right)
{
	return liVector3Generic(x + right.x, y + right.y, z + right.z);
}

template<typename T>
inline liVector3Generic<T> liVector3Generic<T>::operator+=(liVector3Generic right)
{
	*this = *this + right;
	return *this;
}

template<typename T>
inline liVector3Generic<T> liVector3Generic<T>::operator/(liVector3Generic right)
{
	return liVector3Generic(x / right.x, y / right.y, z / right.z);
}

template<typename T>
inline liVector3Generic<T> liVector3Generic<T>::operator/=(liVector3Generic right)
{
	*this = *this / right;
	return *this;
}

template<typename T>
inline liVector3Generic<T> liVector3Generic<T>::operator*(liVector3Generic right)
{
	return liVector3Generic(x * right.x, y * right.y, z * right.z);
}

template<typename T>
inline liVector3Generic<T> liVector3Generic<T>::operator*=(liVector3Generic right)
{
	*this = *this * right;
	return *this;
}

template<typename T>
class liVector4Generic {
public:
	T x = 0, y = 0, z = 0, w = 0;

	liVector4Generic() = default;
	liVector4Generic(T x, T y, T z, T w);
	float Length() const;
	liVector4Generic<T> Normalize();
	T* ToPtr();
	const T* ToPtr() const;
	void Set(T x, T y, T z, T w);
	T& operator[](int index);
	const T& operator[](int index) const;

	liVector4Generic operator-();
	liVector4Generic operator-(liVector4Generic right);
	liVector4Generic operator-=(liVector4Generic right);
	liVector4Generic operator+(liVector4Generic right);
	liVector4Generic operator+=(liVector4Generic right);
	liVector4Generic operator/(liVector4Generic right);
	liVector4Generic operator/=(liVector4Generic right);
	liVector4Generic operator*(liVector4Generic right);
	liVector4Generic operator*=(liVector4Generic right);
};

template<typename T>
inline liVector4Generic<T>::liVector4Generic(T x, T y, T z, T w)
{
	Set(x, y, z, w);
}

template<typename T>
inline float liVector4Generic<T>::Length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

template<typename T>
inline liVector4Generic<T> liVector4Generic<T>::Normalize()
{
	float l = Length();
	Set(x / l, y / l, z / l, w / l);
	return *this;
}

template<typename T>
inline T* liVector4Generic<T>::ToPtr()
{
	return &x;
}

template<typename T>
inline const T* liVector4Generic<T>::ToPtr() const
{
	return (const T*)&x;
}

template<typename T>
inline void liVector4Generic<T>::Set(T x, T y, T z, T w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

template<typename T>
inline T& liVector4Generic<T>::operator[](int index)
{
	return ToPtr()[index];
}

template<typename T>
inline const T& liVector4Generic<T>::operator[](int index) const
{
	return ToPtr()[index];
}

template<typename T>
inline liVector4Generic<T> liVector4Generic<T>::operator-()
{
	return liVector4Generic(-x, -y, -z, -w);
}

template<typename T>
inline liVector4Generic<T> liVector4Generic<T>::operator-(liVector4Generic right)
{
	return liVector4Generic(x - right.x, y - right.y, z - right.z, w - right.w);
}

template<typename T>
inline liVector4Generic<T> liVector4Generic<T>::operator-=(liVector4Generic right)
{
	*this = *this - right;
	return *this;
}

template<typename T>
inline liVector4Generic<T> liVector4Generic<T>::operator+(liVector4Generic right)
{
	return liVector4Generic(x + right.x, y + right.y, z + right.z, w + right.w);
}

template<typename T>
inline liVector4Generic<T> liVector4Generic<T>::operator+=(liVector4Generic right)
{
	*this = *this + right;
	return *this;
}

template<typename T>
inline liVector4Generic<T> liVector4Generic<T>::operator/(liVector4Generic right)
{
	return liVector4Generic(x / right.x, y / right.y, z / right.z, w / right.w);
}

template<typename T>
inline liVector4Generic<T> liVector4Generic<T>::operator/=(liVector4Generic right)
{
	*this = *this / right;
	return *this;
}

template<typename T>
inline liVector4Generic<T> liVector4Generic<T>::operator*(liVector4Generic right)
{
	return liVector4Generic(x * right.x, y * right.y, z * right.z, w * right.w);
}

template<typename T>
inline liVector4Generic<T> liVector4Generic<T>::operator*=(liVector4Generic right)
{
	*this = *this * right;
	return *this;
}

#endif
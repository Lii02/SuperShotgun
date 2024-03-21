#ifndef MATHTYPES_H
#define MATHTYPES_H
#include "Vectors.h"

typedef liVector2Generic<int> liVector2i;
typedef liVector2Generic<float32> liVector2f;
typedef liVector2Generic<float64> liVector2d;

typedef liVector3Generic<int> liVector3i;
typedef liVector3Generic<float32> liVector3f;
typedef liVector3Generic<float64> liVector3d;

typedef liVector4Generic<int> liVector4i;
typedef liVector4Generic<float32> liVector4f;
typedef liVector4Generic<float64> liVector4d;

typedef struct {
	float x, y;
	float w, h;
} liRectangle;

typedef struct {
	liVector3f direction;
	liVector3f origin;
} liRay;

#endif
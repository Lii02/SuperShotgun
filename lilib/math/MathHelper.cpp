#include "MathHelper.h"

float32 liMathHelper::PI = 3.14f;

float32 liMathHelper::ToRadians(float32 d)
{
	return d * liMathHelper::PI / 180;
}

float32 liMathHelper::ToDegrees(float32 r)
{
	return r * 180 / liMathHelper::PI;
}
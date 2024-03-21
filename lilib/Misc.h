#ifndef LILIB_MISC_H
#define LILIB_MISC_H
#include "EngineDefs.h"
#include "LiString.h"

#define LILIB_TIMESEED time(NULL)

timestamp_t LiLib_GetTimestamp();
void LiLib_SetSeed(uint32_t seed);
float LiLib_RandomFloat(float max);
liString LiLib_GetTimeString(time_t timestamp);
uint8_t LiLib_GetNth(uint32_t value, int n);

#endif
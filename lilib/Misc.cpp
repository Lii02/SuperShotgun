#include "Misc.h"

timestamp_t LiLib_GetTimestamp()
{
	return (uint32_t)time(NULL);
}

void LiLib_SetSeed(uint32_t seed)
{
	srand(seed);
}

float LiLib_RandomFloat(float max)
{
	return (float)rand() / (float)(RAND_MAX / max);
}

liString LiLib_GetTimeString(time_t timestamp)
{
	struct tm ts;
	ts = *localtime(&timestamp);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%a%Y%m%d%H%M%S", &ts);
	return liString(buffer);
}

uint8_t LiLib_GetNth(uint32_t value, int n)
{
	return (value >> (n * 8)) & 0xFF;
}
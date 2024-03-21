#include "GUID.h"
#include "Misc.h"

#define GUID_RESERVED 0xDEAF

liString LiLib_GenerateGUID()
{
    liString guid;
    char* guid_string = new char[17];
    memset(guid_string, 0, 17);

    auto time_value = LiLib_GetTimestamp();
    itoa(time_value, guid_string, 16);
    itoa(GUID_RESERVED, guid_string + 8, 16);
    int start = 12;
    for (int i = start; i < 16; i++) {
        uint16_t random = rand() % 0x0F;
        itoa(random, guid_string + i, 16);
    }

    guid.Append(guid_string);
    delete[] guid_string;
    guid.ToUpper();
    return guid;
}
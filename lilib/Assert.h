#ifndef LILIB_ASSERT_H
#define LILIB_ASSERT_H
#include "EngineDefs.h"

void LiLib_Assert(bool expression, cstring message);

#ifdef DEBUG
#define LILIB_ASSERT(expression, message) LiLib_Assert(expression, message);
#else
#define LILIB_ASSERT(...)
#endif

#endif
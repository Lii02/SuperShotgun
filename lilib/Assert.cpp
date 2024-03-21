#include "Assert.h"
#include <cassert>

void LiLib_Assert(bool expression, cstring message)
{
	if (!expression) {
		fprintf(stderr, "%s\n", message);
		assert(expression);
	}
}
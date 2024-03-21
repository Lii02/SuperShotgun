#ifndef RENDERER_ENUMS_H
#define RENDERER_ENUMS_H
#include <lilib/EngineDefs.h>

enum TextureFilter : ubyte {
	FILTER_NEAREST,
	FILTER_LINEAR,
};

enum AlphaBlendingFunc : ubyte {
	ONE_MINUS_SRC,
};

#endif
#ifndef FRAMEWORK_STRUCTS_H
#define FRAMEWORK_STRUCTS_H
#include <lilib/EngineDefs.h>
#include <glrenderer/Texture2D.h>
#include <lilib/Dictionary.h>
#include <lilib/math/MathTypes.h>

struct character_data_t {
	Texture2D* texture;
	liVector2f size, bearing;
	uint32_t advance;
};

typedef liDictionary<char, character_data_t>* FontData;

#endif
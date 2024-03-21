#ifndef GAMEFRAMEWORK_TEXTUREFACTORY_H
#define GAMEFRAMEWORK_TEXTUREFACTORY_H
#include <lilib/EngineDefs.h>
#include <lilib/math/MathTypes.h>
#include <glrenderer/Texture2D.h>

class TextureFactory {
private:
	liVector2i dimensions;
	uint8_t* pixels;
	ubyte bits;
public:
	TextureFactory(liVector2i dimensions, ubyte bits);
	~TextureFactory();
	void SetPixel(liVector2i position, uint32_t color);
	Texture2D* ToGPUTexture();
};

#endif
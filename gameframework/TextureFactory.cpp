#include "TextureFactory.h"
#include <lilib/Misc.h>
#include <lilib/Assert.h>

TextureFactory::TextureFactory(liVector2i dimensions, ubyte bits)
{
	this->dimensions = dimensions;
	this->bits = bits;
	auto bytes = bits / 8;
	this->pixels = new uint8_t[dimensions.x * dimensions.y * bytes];
	LILIB_ASSERT(bits < 32, "TextureFactory is more than 32 bits");
}

TextureFactory::~TextureFactory()
{
	delete[] pixels;
}

void TextureFactory::SetPixel(liVector2i position, uint32_t color)
{
	auto location = position.y * dimensions.x + position.x;
	uint8_t* ptr = pixels + location;
	ptr[0] = LiLib_GetNth(color, 0);
	ptr[1] = LiLib_GetNth(color, 1);
	ptr[2] = LiLib_GetNth(color, 2);
	if (bits == 32) {
		ptr[3] = LiLib_GetNth(color, 3);
	}
}

Texture2D* TextureFactory::ToGPUTexture()
{
	Texture2D* texture = new Texture2D(dimensions.x, dimensions.y, bits / 8);
	texture->SetData(pixels);
	return texture;
}
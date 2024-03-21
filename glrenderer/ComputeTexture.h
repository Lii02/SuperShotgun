#ifndef RENDERER_COMPUTE_TEXTURE_H
#define RENDERER_COMPUTE_TEXTURE_H
#include <lilib/EngineDefs.h>
#include "RendererEnums.h"

class ComputeTexture {
private:
	uint32_t ID, width, height, bpp;
	TextureFilter filter;
public:
	ComputeTexture(uint32_t width, uint32_t height, uint32_t bpp, TextureFilter filter = TextureFilter::FILTER_NEAREST);
	~ComputeTexture();

	void Initialize();
	void Shutdown();
};

#endif
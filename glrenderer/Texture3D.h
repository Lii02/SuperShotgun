#ifndef RENDERER_TEXTURE3D_H
#define RENDERER_TEXTURE3D_H
#include <lilib/EngineDefs.h>
#include "RendererEnums.h"

class Texture3D {
private:
	uint32_t ID, width, height, bpp;
public:
	Texture3D(uint32_t width, uint32_t height, uint32_t bpp);
	~Texture3D();

	void Initialize();
	void Shutdown();
	void Bind();
	void Unbind();
	void SetData(int face, void* data);
};

#endif
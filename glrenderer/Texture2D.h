#ifndef RENDERER_TEXTURE_2D
#define RENDERER_TEXTURE_2D
#include <lilib/EngineDefs.h>
#include <lilib/LiString.h>
#include "RendererEnums.h"

#define MIN_TEXTURES 0
#define MAX_TEXTURES 32

class Texture2D {
private:
	uint32_t ID, width, height, bpp;
	TextureFilter filter;
	bool swapped_channels;
	
	bool copied;
	bool from_file;
	liString filepath;
public:
	Texture2D(uint32_t width, uint32_t height, uint32_t bpp, bool swapped_channels = false, TextureFilter filter = TextureFilter::FILTER_NEAREST);
	Texture2D(uint32_t ID);
	~Texture2D();

	void Initialize();
	void Shutdown();
	void SetFileData(bool from_file, liString filepath);
	liString GetFilepath();
	void Bind(ubyte unit = 0);
	void Unbind();
	void SetData(void* data);
	void SetID(uint32_t new_id);
	uint32_t GetID() const;
	void SetFilter(TextureFilter filter);
	uint32_t GetWidth() const;
	uint32_t GetHeight() const;
	bool IsCopied() const;
	// These functions dont set anything on the gpu

	void SetDimensions(uint32_t width, uint32_t height);
	void SetBPP(uint32_t bpp);
};

#endif
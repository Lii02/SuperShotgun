#include "ComputeTexture.h"
#include "Wrapper.h"

ComputeTexture::ComputeTexture(uint32_t width, uint32_t height, uint32_t bpp, TextureFilter filter)
{
	this->width = width;
	this->height = height;
	this->bpp = bpp;
	this->filter = filter;
	Initialize();
}

ComputeTexture::~ComputeTexture()
{
	Shutdown();
}

void ComputeTexture::Initialize()
{
	glGenTextures(1, &ID);
}

void ComputeTexture::Shutdown()
{
	glDeleteTextures(1, &ID);
}
#include "Texture3D.h"
#include "Wrapper.h"
#include "MiscFunctions.h"

Texture3D::Texture3D(uint32_t width, uint32_t height, uint32_t bpp)
{
	this->width = width;
	this->height = height;
	this->bpp = bpp;
	Initialize();
}

Texture3D::~Texture3D()
{
	Shutdown();
}

void Texture3D::Initialize()
{
	glGenTextures(1, &ID);
	for (int i = 0; i < 6; i++) {
		SetData(i, NULL);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture3D::Shutdown()
{
	glDeleteTextures(1, &ID);
}

void Texture3D::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void Texture3D::Unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture3D::SetData(int face, void* data)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	auto f = MiscRendererFunctions::GetTextureFormat(bpp);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + f, 0, f, width, height, 0, f, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}
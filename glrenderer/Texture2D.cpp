#include "Texture2D.h"
#include "Wrapper.h"
#include "MiscFunctions.h"
#include <lilib/Assert.h>

Texture2D::Texture2D(uint32_t width, uint32_t height, uint32_t bpp, bool swapped_channels, TextureFilter filter)
{
	this->width = width;
	this->height = height;
	this->bpp = bpp;
	this->filter = filter;
	this->swapped_channels = swapped_channels;
	this->copied = false;
	Initialize();
}

Texture2D::Texture2D(uint32_t ID)
{
	this->ID = ID;
	this->copied = true;
}

Texture2D::~Texture2D()
{
	Shutdown();
}

void Texture2D::Initialize()
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	auto f = MiscRendererFunctions::GetFilterDefinition(filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Shutdown()
{
	if(!copied)
		glDeleteTextures(1, &ID);
}

void Texture2D::SetFileData(bool from_file, liString filepath)
{
	this->from_file = from_file;
	this->filepath = filepath;
}

liString Texture2D::GetFilepath()
{
	return filepath;
}

void Texture2D::Bind(ubyte unit)
{
	LILIB_ASSERT(unit >= MIN_TEXTURES && unit <= MAX_TEXTURES, "Texture unit is out of bounds!");
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::SetData(void* data)
{
	glBindTexture(GL_TEXTURE_2D, ID);
	if (swapped_channels) {
		glTexImage2D(GL_TEXTURE_2D, 0, MiscRendererFunctions::GetTextureFormat(bpp), width, height, 0, MiscRendererFunctions::GetSwappedTextureFormat(bpp), GL_UNSIGNED_BYTE, data);
	} else {
		auto f = MiscRendererFunctions::GetTextureFormat(bpp);
		glTexImage2D(GL_TEXTURE_2D, 0, f, width, height, 0, f, GL_UNSIGNED_BYTE, data);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::SetID(uint32_t new_id)
{
	this->copied = true;
	this->ID = new_id;
}

uint32_t Texture2D::GetID() const
{
	return ID;
}

void Texture2D::SetFilter(TextureFilter filter)
{
	glBindTexture(GL_TEXTURE_2D, ID);
	auto f = MiscRendererFunctions::GetFilterDefinition(filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, f);
	glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t Texture2D::GetWidth() const
{
	return width;
}

uint32_t Texture2D::GetHeight() const
{
	return height;
}

bool Texture2D::IsCopied() const
{
	return copied;
}

void Texture2D::SetDimensions(uint32_t width, uint32_t height)
{
	this->width = width;
	this->height = height;
}

void Texture2D::SetBPP(uint32_t bpp)
{
	this->bpp = bpp;
}
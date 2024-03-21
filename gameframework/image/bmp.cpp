#include "bmp.h"

liBMP* liBMP::Load(liFile* file)
{
    auto file_data = file->Read();
    size_t file_size = file_data.Length();
    ubytebuffer buffer = new ubyte[file_size];
    memcpy(buffer, &file_data[0], file_size);
	liBMP* bmp = new liBMP(file);

    ubyte* ptr = buffer;
    memcpy(&bmp->header, ptr, sizeof(liBMPHeader));
    ptr += sizeof(liBMPHeader);
    memcpy(&bmp->imageheader, ptr, sizeof(liBMPImageHeader));
    ptr += sizeof(liBMPImageHeader);
    if (bmp->imageheader.bits <= 8) {
        uint8_t* color_ptr = (uint8_t*)&bmp->colors;
        unsigned color_block_length = sizeof(liBMPColor) * 0xFF;
        memcpy(color_ptr, ptr, color_block_length);
        ptr += color_block_length;
    }
    ptr = buffer + bmp->header.offset;
    size_t imagesize = bmp->imageheader.width * bmp->imageheader.height * bmp->GetBPP();
    bmp->imageheader.imagesize = imagesize;
    bmp->pixels = new uint8_t[imagesize];
    memcpy(bmp->pixels, ptr, imagesize);

    delete[] buffer;
	return bmp;
}

liBMP::liBMP(liFile* fileptr) : liAsset(fileptr)
{
}

liBMP::~liBMP()
{
	delete[] pixels;
}

int liBMP::GetWidth() const
{
	return imageheader.width;
}

int liBMP::GetHeight() const
{
	return imageheader.height;
}

int liBMP::GetBPP() const
{
    return imageheader.bits / 8;
}

void* liBMP::GetPixels() const
{
	return pixels;
}

void liBMP::FlipVertically()
{
    uint64_t stride = imageheader.width * GetBPP();
    uint8_t* row = new uint8_t[stride];
    uint8_t* low = (ubyte*)pixels;
    uint8_t* high = &((ubyte*)pixels)[(imageheader.height - 1) * stride];

    for (; low < high; low += stride, high -= stride) {
        memcpy(row, low, stride);
        memcpy(low, high, stride);
        memcpy(high, row, stride);
    }
    delete[] row;
}

Texture2D* liBMP::ToTexture(bool flip)
{
	if(flip)
		FlipVertically();
    Texture2D* texture = new Texture2D(GetWidth(), GetHeight(), GetBPP(), true, TextureFilter::FILTER_NEAREST);
    texture->SetData(pixels);
    texture->SetFileData(true, fileptr->GetShortPath());
	return texture;
}
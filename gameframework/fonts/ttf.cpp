#include "ttf.h"
#include <glrenderer/Wrapper.h>
#include <FreeType/freetype/freetype.h>
#include <FreeType/ft2build.h>

liTTF::liTTF(liFile* file, float font_size) : liAsset(file)
{
    this->font_size = font_size;
}

liTTF::~liTTF()
{
    for (size_t i = 0; i < glyphs.Size(); i++) {
        delete glyphs.At(i).second.texture;
    }
}

FontData liTTF::GetFontData()
{
	return &glyphs;
}

float liTTF::GetFontSize() const
{
    return font_size;
}

liTTF* liTTF::Load(liFile* file, float font_size)
{
	liTTF* ttf = new liTTF(file, font_size);
    ttf->font_size = font_size;
	auto file_data = file->Read();
	size_t file_size = file_data.Length();
	ubytebuffer buffer = new ubyte[file_size];
    memcpy(buffer, &file_data[0], file_size);
	FT_Library ft;
	FT_Init_FreeType(&ft);
	FT_Face face;
    FT_New_Memory_Face(ft, buffer, file_size, 0, &face);
	FT_Set_Pixel_Sizes(face, 0, font_size);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char i = 0; i < UCHAR_MAX; i++) {
        FT_Load_Char(face, i, FT_LOAD_RENDER);
        Texture2D* texture = new Texture2D(face->glyph->bitmap.width, face->glyph->bitmap.rows, 1, false);
        texture->SetData(face->glyph->bitmap.buffer);
        character_data_t character = {
            texture,
            liVector2f(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            liVector2f(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        ttf->glyphs.Push(i, character);
	}

    delete[] buffer;
    FT_Done_Face(face);
	FT_Done_FreeType(ft);
	return ttf;
}
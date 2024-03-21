#ifndef BMP_H
#define BMP_H
#include <lilib/EngineDefs.h>
#include <gameframework/File.h>
#include <gameframework/Asset.h>
#include <glrenderer/Texture2D.h>

#pragma pack(push, 1)
struct liBMPHeader {
	int16_t type;
	uint32_t filesize;
	int32_t reserved;
	uint32_t offset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct liBMPImageHeader {
	uint32_t headersize;
	int32_t width;
	int32_t height;
	uint16_t planes;
	uint16_t bits;
	uint32_t compression;
	uint32_t imagesize;
	int32_t xppm;
	int32_t yppm;
	uint32_t totalcolors;
	uint32_t importantcolors;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct liBMPColor {
	union {
		uint32_t color;

		struct {
			uint8_t blue;
			uint8_t green;
			uint8_t red;
			uint8_t reserved;
		};
	};
};
#pragma pack(pop)

#define BMP_PALETTE_SIZE 0xFF

class liBMP : public liAsset {
private:
	liBMPHeader header;
	liBMPImageHeader imageheader;
	liBMPColor colors[BMP_PALETTE_SIZE];
	void* pixels;
public:
	static liBMP* Load(liFile* file);
	
	liBMP(liFile* fileptr);
	~liBMP();
	int GetWidth() const;
	int GetHeight() const;
	int GetBPP() const;
	void* GetPixels() const;
	void FlipVertically();
	Texture2D* ToTexture(bool flip = true);
};

#endif
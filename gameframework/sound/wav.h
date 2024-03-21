#ifndef SND_WAV_H
#define SND_WAV_H
#include <lilib/EngineDefs.h>
#include <gameframework/File.h>
#include <gameframework/Asset.h>

#define WAV_DESC_SIZE 4

#pragma pack(push, 1)
struct liWAVInfo {
	char signature[WAV_DESC_SIZE];
	uint32_t filesize;
	char wav_desc[WAV_DESC_SIZE];
	char fmt_desc[WAV_DESC_SIZE];
	uint32_t wav_section_size;
	uint16_t type_format;
	uint16_t channels;
	uint32_t frequency;
	uint32_t rate;
	uint16_t alignment;
	uint16_t bits_sample;
	char data_desc[WAV_DESC_SIZE];
	uint32_t data_size;
};
#pragma pack(pop)

class liWAV : public liAsset {
private:
	liWAVInfo info;
	void* data;
public:
	static liWAV* Load(liFile* file);
	
	liWAV(liFile* fileptr);
	~liWAV();

	void* GetData();
	liWAVInfo GetInfo() const;
};

#endif
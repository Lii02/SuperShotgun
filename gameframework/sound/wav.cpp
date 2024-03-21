#include "wav.h"

liWAV* liWAV::Load(liFile* file)
{
	auto file_data = file->Read();
	size_t file_size = file_data.Length();
	ubytebuffer buffer = new ubyte[file_size];
	memcpy(buffer, &file_data[0], file_size);
	liWAV* wav = new liWAV(file);
	
	uint8_t* ptr = buffer;
	memcpy(&wav->info, ptr, sizeof(liWAVInfo));
	ptr += sizeof(liWAVInfo);
	wav->data = new uint8_t[wav->info.data_size];
	memcpy(wav->data, ptr, wav->info.data_size);

	delete[] buffer;
	return wav;
}

liWAV::liWAV(liFile* fileptr) : liAsset(fileptr)
{
}

liWAV::~liWAV()
{
	delete[] data;
}

void* liWAV::GetData()
{
	return data;
}

liWAVInfo liWAV::GetInfo() const
{
	return info;
}
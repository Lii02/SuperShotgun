#include "AudioBuffer.h"
#include <thirdparty/al.h>

AudioBuffer::AudioBuffer()
{
	Initialize();
}

AudioBuffer::~AudioBuffer()
{
	Shutdown();
}

void AudioBuffer::Initialize()
{
	alGenBuffers(1, &ID);
}

void AudioBuffer::Shutdown()
{
	alDeleteBuffers(1, &ID);
}

void AudioBuffer::SetData(uint32_t format, void* data, uint32_t size, uint32_t freq)
{
	alBufferData(ID, format, data, size, freq);
}

uint32_t AudioBuffer::GetID()
{
	return ID;
}
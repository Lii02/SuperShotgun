#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H
#include <lilib/EngineDefs.h>

class AudioBuffer {
private:
	uint32_t ID;
public:
	AudioBuffer();
	~AudioBuffer();

	void Initialize();
	void Shutdown();
	void SetData(uint32_t format, void* data, uint32_t size, uint32_t freq);
	uint32_t GetID();
};

#endif
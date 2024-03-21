#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H
#include <lilib/EngineDefs.h>
#include <thirdparty/alc.h>
#include <lilib/math/MathTypes.h>
#include "AudioSource.h"
#include "AudioBuffer.h"

struct AudioEngineListener {
	liVector3f position;
	liVector3f velocity;
	liVector3f orientation;
};

struct audioengine_vars_t {
	ALCdevice* device;
	ALCcontext* context;
	AudioEngineListener listener;
};

void AudioEngine_Startup();
void AudioEngine_Shutdown();
void AudioEngine_SetListenerData(liVector3f position, liVector3f velocity, liVector3f orientation);
AudioEngineListener AudioEngine_GetListener();
uint32_t AudioEngine_GetFormat(uint16_t channels, uint16_t samples);

extern audioengine_vars_t ae_vars;

#endif
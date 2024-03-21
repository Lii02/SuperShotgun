#include "AudioEngine.h"
#include <thirdparty/al.h>

static audioengine_vars_t ae_vars;

void AudioEngine_Startup()
{
	ae_vars.device = alcOpenDevice(NULL);
	ae_vars.context = alcCreateContext(ae_vars.device, NULL);
	alcMakeContextCurrent(ae_vars.context);
}

void AudioEngine_Shutdown()
{
	ae_vars.device = alcGetContextsDevice(ae_vars.context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(ae_vars.context);
	alcCloseDevice(ae_vars.device);
}

void AudioEngine_SetListenerData(liVector3f position, liVector3f velocity, liVector3f orientation)
{
	ae_vars.listener.position = position;
	ae_vars.listener.velocity = velocity;
	ae_vars.listener.orientation = orientation;

	float orientation_floats[6] = { orientation.x, orientation.y, orientation.z, 0.0f, 1.0f, 0.0f };
	alListener3f(AL_POSITION, position.x, position.y, position.z);
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	alListenerfv(AL_ORIENTATION, orientation_floats);
}

AudioEngineListener AudioEngine_GetListener()
{
	return ae_vars.listener;
}

uint32_t AudioEngine_GetFormat(uint16_t channels, uint16_t samples)
{
	bool stereo = (channels > 1);

	switch (samples) {
	case 16:
		if (stereo)
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_MONO16;
	case 8:
		if (stereo)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_MONO8;
	default:
		return -1;
	}
}
#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H
#include <lilib/EngineDefs.h>
#include <lilib/math/MathTypes.h>
#include "AudioBuffer.h"

class AudioSource {
private:
	unsigned int ID;
public:
	float pitch, gain;
	liVector3f position, velocity;
	bool loop;

	AudioSource();
	~AudioSource();
	void Initialize();
	void Shutdown();

	void UpdatePitch(float pitch);
	void UpdateGain(float gain);
	void UpdatePosition(liVector3f position);
	void UpdateVelocity(liVector3f vel);
	void BindBuffer(AudioBuffer buffer);
	void Play();
	void Stop();
	void Continue();
	bool IsPlaying();
	void SetLooping(bool loop);
};

#endif
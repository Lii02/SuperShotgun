#include "AudioSource.h"
#include <thirdparty/al.h>

AudioSource::AudioSource()
{
	Initialize();
	this->pitch = 1.0f;
	UpdatePitch(pitch);
	this->gain = 1.0f;
	UpdateGain(pitch);
	this->loop = false;
	SetLooping(loop);
}

AudioSource::~AudioSource()
{
	Shutdown();
}

void AudioSource::Initialize()
{
	alGenSources(1, &ID);
}

void AudioSource::Shutdown()
{
	Stop();
	alDeleteSources(1, &ID);
}

void AudioSource::UpdatePitch(float pitch)
{
	this->pitch = pitch;
	alSourcef(ID, AL_PITCH, pitch);
}

void AudioSource::UpdateGain(float gain)
{
	this->gain = gain;
	alSourcef(ID, AL_GAIN, gain);
}

void AudioSource::UpdatePosition(liVector3f position)
{
	this->position = position;
	alSource3f(ID, AL_POSITION, position.x, position.y, position.z);
}

void AudioSource::UpdateVelocity(liVector3f vel)
{
	this->velocity = vel;
	alSource3f(ID, AL_VELOCITY, vel.x, vel.y, vel.z);
}

void AudioSource::BindBuffer(AudioBuffer buffer)
{
	alSourcei(ID, AL_BUFFER, buffer.GetID());
}

void AudioSource::Play()
{
	Stop();
	Continue();
}

void AudioSource::Stop()
{
	alSourceStop(ID);
}

void AudioSource::Continue()
{
	alSourcePlay(ID);
}

bool AudioSource::IsPlaying()
{
	int state;
	alGetSourcei(ID, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}

void AudioSource::SetLooping(bool loop)
{
	this->loop = loop;
	alSourcei(ID, AL_LOOPING, loop);
}
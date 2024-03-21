#include "Light.h"

liLight::liLight(liLightType type, liVector3f color, float intensity, float radius, float linear, float quadratic, float cutoff)
	: liActor(liActorType::TYPE_LIGHT, liActorFlag::FLAG_3D)
{
	this->type = type;
	this->color = color;
	this->intensity = intensity;
	this->radius = radius;
	this->linear = linear;
	this->quadratic = quadratic;
	this->cutoff = cutoff;
}

void liLight::Spawn()
{
	liActor::Spawn();
}

void liLight::Shutdown()
{
	liActor::Shutdown();
}

void liLight::Render(RenderShader* shader)
{
	liActor::Render(shader);
}

void liLight::Update()
{
	liActor::Update();
}
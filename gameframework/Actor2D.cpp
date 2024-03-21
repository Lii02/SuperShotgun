#include "Actor2D.h"
#include "Profiler.h"

liActor2D::liActor2D()
	: liActor(liActorType::TYPE_ACTOR2D, liActorFlag::FLAG_2D)
{
	this->sprite = new Sprite;
}

liActor2D::~liActor2D()
{
	Shutdown();
}

Sprite* liActor2D::GetSprite()
{
	return sprite;
}

void liActor2D::SetImage(Texture2D* image)
{
	sprite->SetImage(image);
}

void liActor2D::SetShader(RenderShader* shader)
{
	this->shader = shader;
}

void liActor2D::Spawn()
{
	liActor::Spawn();
}

void liActor2D::Shutdown()
{
	liActor::Shutdown();
	delete sprite;
}

void liActor2D::Render(RenderShader* shader)
{
	liActor::Render(shader);
	LoadTransform(shader->GetProgram());
	sprite->Draw();
}

void liActor2D::Update()
{
	liActor::Update();
}
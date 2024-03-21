#include "GUITexture.h"
#include <glrenderer/GUIGraphics.h>

liGUITexture::liGUITexture(Texture2D* image, liVector3f tint)
	: liActor(liActorType::TYPE_GUITEXTURE, liActorFlag::FLAG_GUI)
{
	this->tag = "Texture";
	this->image = image;
	this->tint = tint;
}

liGUITexture::~liGUITexture()
{
	Shutdown();
}

void liGUITexture::Spawn()
{
	liActor::Spawn();
}

void liGUITexture::Shutdown()
{
	liActor::Shutdown();
	delete image;
}

void liGUITexture::Render(RenderShader* shader)
{
	liActor::Render(shader);
	shader->Bind();
	shader->GetProgram()->LoadVec3f("tint", tint);
	LoadTransform(shader->GetProgram());
	GUIGraphics::Draw(image);
	shader->Unbind();
}

void liGUITexture::Update()
{
	liActor::Update();
}

Texture2D* liGUITexture::GetImage()
{
	return image;
}

void liGUITexture::SetImage(Texture2D* texture)
{
	delete image;
	this->image = texture;
}
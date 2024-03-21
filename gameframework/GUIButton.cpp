#include "GUIButton.h"

liGUIButton::liGUIButton(liTTF* font, Texture2D* image, liString text, liVector4f color)
	: liActor(liActorType::TYPE_GUIBUTTON, liActorFlag::FLAG_GUI)
{
	this->tag = "Button";
	texture = (liGUITexture*)AddChild(new liGUITexture(image));
	label = (liLabel*)AddChild(new liLabel(font, text, color));
	auto w = texture->GetImage()->GetWidth();
	auto h = texture->GetImage()->GetHeight();
	texture->transform.scale = liVector3f(w, h, 1);
}

liGUIButton::~liGUIButton()
{
}

void liGUIButton::Spawn()
{
	liActor::Spawn();
}

void liGUIButton::Shutdown()
{
	liActor::Shutdown();
}

void liGUIButton::Render(RenderShader* shader)
{
	liActor::Render(shader);
}

void liGUIButton::Update()
{
	liActor::Update();
}

bool liGUIButton::OnClick() const
{
	return false;
}
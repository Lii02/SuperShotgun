#include "Label.h"
#include <glrenderer/FontGraphics.h>

liLabel::liLabel(liTTF* font, liString text, liVector4f color, int kerning)
	: liActor(liActorType::TYPE_LABEL, liActorFlag::FLAG_GUI)
{
	this->tag = "Label";
	this->font = font;
	this->text = text;
	this->color = color;
	this->kerning = kerning;
}

liLabel::~liLabel()
{
}

void liLabel::Spawn()
{
	liActor::Spawn();
}

void liLabel::Shutdown()
{
	liActor::Shutdown();
}

void liLabel::Render(RenderShader* shader)
{
	liActor::Render(shader);
	shader->Bind();
	shader->GetProgram()->LoadVec4f("text_color", color);
	LoadTransform(shader->GetProgram());
	FontGraphics::DrawString(font->GetFontData(), text, kerning);
	shader->Unbind();
}

void liLabel::Update()
{
	liActor::Update();
}

liTTF* liLabel::GetFont()
{
	return font;
}

float liLabel::GetLabelWidth()
{
	return FontGraphics::CalculateWidth(font->GetFontData(), text, kerning);
}
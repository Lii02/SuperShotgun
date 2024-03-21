#include "HDR.h"
#include "ShaderAsset.h"

HDREffect::HDREffect(float exposure, liContentManager* content, liVector2i screen)
	: IEffect(content, NULL, screen)
{
	this->exposure = exposure;
	this->shader = liShaderAsset::CreateShader(content->LoadAsset<liShaderAsset>("quad.vsh"), content->LoadAsset<liShaderAsset>("hdr.fsh"), { "position" });
}

HDREffect::~HDREffect()
{
}

void HDREffect::Update()
{
	shader->Bind();
	shader->GetProgram()->LoadFloat("exposure", exposure);
	shader->Unbind();
}
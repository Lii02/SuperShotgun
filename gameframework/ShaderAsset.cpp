#include "ShaderAsset.h"

liShaderAsset::liShaderAsset(liFile* file) : liAsset(file)
{
}

liString* liShaderAsset::GetSource()
{
	return &source;
}

void liShaderAsset::SetSource(liString new_source)
{
	this->source = new_source;
}

RenderShader* liShaderAsset::CreateShader(liShaderAsset* vertex, liShaderAsset* fragment, liList<cstring> attribs)
{
	RenderShader* shader = new RenderShader();
	shader->Initialize(attribs, vertex->GetSource()->c_str(), fragment->GetSource()->c_str());
	return shader;
}
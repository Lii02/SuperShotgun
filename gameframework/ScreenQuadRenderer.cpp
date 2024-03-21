#include "ScreenQuadRenderer.h"
#include <glrenderer/ScreenQuad.h>
#include <glrenderer/MiscFunctions.h>
#include "ShaderAsset.h"

ScreenQuadRenderer::ScreenQuadRenderer(liContentManager* content)
{
	Initialize(content);
}

ScreenQuadRenderer::~ScreenQuadRenderer()
{
	Shutdown();
}

void ScreenQuadRenderer::Initialize(liContentManager* content)
{
	quadshader = liShaderAsset::CreateShader(content->LoadAsset<liShaderAsset>("quad.vsh"), content->LoadAsset<liShaderAsset>("quad.fsh"), { "position" });
}

void ScreenQuadRenderer::Shutdown()
{
	delete quadshader;
}

void ScreenQuadRenderer::Present()
{
	quadshader->Bind();
	quadshader->GetProgram()->LoadInt("color_texture", 0);
	ScreenQuad::Instance->Draw();
	quadshader->Unbind();
}
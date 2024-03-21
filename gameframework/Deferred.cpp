#include "Deferred.h"
#include "ShaderAsset.h"
#include <glrenderer/MiscFunctions.h>
#include <glrenderer/ScreenQuad.h>

DeferredRenderer::DeferredRenderer(liVector2i screen, liContentManager* content)
{
	Initialize(screen, content);
}

DeferredRenderer::~DeferredRenderer()
{
	Shutdown();
}

void DeferredRenderer::Initialize(liVector2i screen, liContentManager* content)
{
	gbuffer_shader = liShaderAsset::CreateShader(content->LoadAsset<liShaderAsset>("gbuffer.vsh"), content->LoadAsset<liShaderAsset>("gbuffer.fsh"), { "position", "textures", "normals" });

	gbuffer = new Framebuffer(screen.x, screen.y);
	gbuffer->Bind();
	gbuffer->AddFloatColorTexture(0);
	gbuffer->AddFloatColorTexture(1);
	gbuffer->AddUByteColorTexture(2);
	gbuffer->AddFloatColorTexture(3);
	gbuffer->AddFloatColorTexture(4);
	gbuffer->DrawBuffers();
	gbuffer->AddDepthRenderbuffer();
	gbuffer->Unbind();

	finalbuffer = new Framebuffer(screen.x, screen.y);
	finalbuffer->Bind();
	finalbuffer->AddFloatColorTexture();
	finalbuffer->AddDepthStencilRenderbuffer();
	finalbuffer->Unbind();
}

void DeferredRenderer::Shutdown()
{
	delete gbuffer;
	delete finalbuffer;
	delete gbuffer_shader;
}

void DeferredRenderer::Render(void(*render_actors)(liList<liActor*>* actors, RenderShader* shader), liList<liActor*>* actors, RenderShader* render_shader)
{
	gbuffer->Bind();
	MiscRendererFunctions::Clear();
	gbuffer_shader->Bind();
	render_actors(actors, gbuffer_shader);
	gbuffer_shader->Unbind();
	gbuffer->Unbind();

	finalbuffer->Bind();
	MiscRendererFunctions::Clear();
	gbuffer->BindTextures();
	render_shader->Bind();
	render_shader->GetProgram()->LoadInt("gPosition", 0);
	render_shader->GetProgram()->LoadInt("gNormal", 1);
	render_shader->GetProgram()->LoadInt("gAlbedo", 2);
	render_shader->GetProgram()->LoadInt("gSpecular", 3);
	render_shader->GetProgram()->LoadInt("gDepth", 4);
	ScreenQuad::Instance->Draw();
	render_shader->Unbind();
	gbuffer->UnbindTextures();
	finalbuffer->Unbind();
}

void DeferredRenderer::Update(liCamera* camera)
{
	MiscRendererFunctions::LoadMatrices(gbuffer_shader->GetProgram(), camera->GetProjectionMatrix(), camera->GetViewMatrix());
}

liList<uint32_t> DeferredRenderer::GetGBufferTextures()
{
	return gbuffer->GetTextures();
}

uint32_t DeferredRenderer::GetFinalTexture() const
{
	return finalbuffer->GetTexture(0);
}
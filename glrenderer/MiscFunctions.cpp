#include "MiscFunctions.h"

void MiscRendererFunctions::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MiscRendererFunctions::ClearColor(float r, float g, float b)
{
	glClearColor(r, g, b, 1);
}

void MiscRendererFunctions::SetVsync(bool vsync)
{
#ifdef ENGINE_WINDOWS
	wglSwapIntervalEXT(vsync);
#endif
}

uint32_t MiscRendererFunctions::GetFilterDefinition(TextureFilter filter)
{
	switch (filter) {
	case TextureFilter::FILTER_LINEAR:
		return GL_LINEAR;
	case TextureFilter::FILTER_NEAREST:
		return GL_NEAREST;
	}
}

uint32_t MiscRendererFunctions::GetTextureFormat(int bpp)
{
	switch (bpp) {
	case 1:
		return GL_RED;
	case 3:
		return GL_RGB;
	case 4:
		return GL_RGBA;
	}
}

uint32_t MiscRendererFunctions::GetSwappedTextureFormat(int bpp)
{
	switch (bpp) {
	case 3:
		return GL_BGR;
	case 4:
		return GL_BGRA;
	}
}

cstring MiscRendererFunctions::GetRenderer()
{
	return (cstring)glGetString(GL_RENDERER);
}

cstring MiscRendererFunctions::GetVendor()
{
	return (cstring)glGetString(GL_VENDOR);
}

cstring MiscRendererFunctions::GetGLVersion()
{
	return (cstring)glGetString(GL_VERSION);
}

void MiscRendererFunctions::SetViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void MiscRendererFunctions::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void MiscRendererFunctions::DisableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}

void MiscRendererFunctions::EnableWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void MiscRendererFunctions::DisableWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void MiscRendererFunctions::LoadMatrices(ShaderProgram* program, liMatrix4x4 projection, liMatrix4x4 view)
{
	program->Bind();
	program->LoadMat4x4("projection", projection);
	program->LoadMat4x4("view", view);
	program->Unbind();
}

void MiscRendererFunctions::EnableBlending()
{
	glEnable(GL_BLEND);
}

void MiscRendererFunctions::DisableBlending()
{
	glDisable(GL_BLEND);
}

void MiscRendererFunctions::SetAlphaBlending(AlphaBlendingFunc func)
{
	int gl = 0;
	switch (func) {
	case AlphaBlendingFunc::ONE_MINUS_SRC:
		gl = GL_ONE_MINUS_SRC_ALPHA;
	}
	glBlendFunc(GL_SRC_ALPHA, gl);
}

void MiscRendererFunctions::EnableBackfaceCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MiscRendererFunctions::DisableBackfaceCulling()
{
	glDisable(GL_CULL_FACE);
}

void MiscRendererFunctions::Prepare2D()
{
	MiscRendererFunctions::DisableBackfaceCulling();
	MiscRendererFunctions::DisableDepthTest();
}

void MiscRendererFunctions::Close2D()
{
	MiscRendererFunctions::EnableDepthTest();
	MiscRendererFunctions::EnableBackfaceCulling();
}

void MiscRendererFunctions::SetViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void MiscRendererFunctions::DirectBindTexture(uint32_t ID, ubyte unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void MiscRendererFunctions::EnableDepthmask()
{
	glDepthMask(GL_TRUE);
}

void MiscRendererFunctions::DisableDepthmask()
{
	glDepthMask(GL_FALSE);
}
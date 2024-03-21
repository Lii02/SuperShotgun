#ifndef RENDERER_MISCFUNCTIONS_H
#define RENDERER_MISCFUNCTIONS_H
#include "Wrapper.h"
#include "RendererEnums.h"
#include "ShaderProgram.h"
#include <lilib/EngineDefs.h>

struct MiscRendererFunctions {
	static void Clear();
	static void ClearColor(float r, float g, float b);
	static void SetVsync(bool vsync);
	static uint32_t GetFilterDefinition(TextureFilter filter);
	static uint32_t GetTextureFormat(int bpp);
	static uint32_t GetSwappedTextureFormat(int bpp);
	static cstring GetRenderer();
	static cstring GetVendor();
	static cstring GetGLVersion();
	static void SetViewport(int x, int y, int width, int height);
	static void EnableDepthTest();
	static void DisableDepthTest();
	static void EnableWireframe();
	static void DisableWireframe();
	static void LoadMatrices(ShaderProgram* program, liMatrix4x4 projection, liMatrix4x4 view);
	static void EnableBlending();
	static void DisableBlending();
	static void SetAlphaBlending(AlphaBlendingFunc func);
	static void EnableBackfaceCulling();
	static void DisableBackfaceCulling();
	static void Prepare2D();
	static void Close2D();
	static void SetViewport(int width, int height);
	static void DirectBindTexture(uint32_t ID, ubyte unit = 0);
	static void EnableDepthmask();
	static void DisableDepthmask();
};

#endif
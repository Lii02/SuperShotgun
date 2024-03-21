#ifndef RENDERER_SKYBOX_H
#define RENDERER_SKYBOX_H
#include <lilib/EngineDefs.h>
#include "RenderShader.h"
#include "Texture3D.h"

extern uint32_t skybox_vao, skybox_vbo;

class Skybox {
private:
	RenderShader* shader;
	Texture3D* cubemap;
public:
	static void InitializeSkyboxGraphics();
	static void ShutdownSkyboxGraphics();
	
	Skybox(RenderShader* shader, Texture3D* cubemap);
	void Draw();
};

#endif
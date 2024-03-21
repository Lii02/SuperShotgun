#ifndef GAMEFRAMEWORK_DEFERRED_H
#define GAMEFRAMEWORK_DEFERRED_H
#include <lilib/EngineDefs.h>
#include <glrenderer/Framebuffer.h>
#include <glrenderer/RenderShader.h>
#include <lilib/math/MathTypes.h>
#include "ScreenQuadRenderer.h"
#include "ContentManager.h"
#include "Actor.h"
#include "Camera.h"

class DeferredRenderer {
private:
	RenderShader* gbuffer_shader;
	Framebuffer* gbuffer, *finalbuffer;
public:
	DeferredRenderer(liVector2i screen, liContentManager* content);
	~DeferredRenderer();

	void Initialize(liVector2i screen, liContentManager* content);
	void Shutdown();
	void Render(void (*render_actors)(liList<liActor*>* actors, RenderShader* shader), liList<liActor*>* actors, RenderShader* render_shader);
	void Update(liCamera* camera);
	liList<uint32_t> GetGBufferTextures();
	uint32_t GetFinalTexture() const;
};

#endif
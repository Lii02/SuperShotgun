#ifndef GAMEFRAMEWORK_IEFFECT_H
#define GAMEFRAMEWORK_IEFFECT_H
#include <lilib/EngineDefs.h>
#include <lilib/math/MathTypes.h>
#include <glrenderer/RenderShader.h>
#include <glrenderer/Framebuffer.h>
#include <glrenderer/ScreenQuad.h>
#include <glrenderer/MiscFunctions.h>
#include <gameframework/ContentManager.h>

class IEffect {
protected:
	RenderShader* shader;
	Framebuffer* fbuffer;
	liContentManager* content;
public:
	IEffect(liContentManager* content, RenderShader* shader, liVector2i screen) {
		this->content = content;
		this->shader = shader;
		this->fbuffer = new Framebuffer(screen.x, screen.y);
		fbuffer->Bind();
		fbuffer->AddFloatColorTexture();
		fbuffer->AddDepthRenderbuffer();
		fbuffer->Unbind();
	}

	virtual ~IEffect() {
		delete shader;
		delete fbuffer;
	}

	void SetShader(RenderShader* shader) {
		this->shader = shader;
	}

	void Process(uint32_t final_texture) {
		fbuffer->Bind();
		shader->Bind();
		MiscRendererFunctions::DirectBindTexture(final_texture);
		ScreenQuad::Instance->Draw();
		MiscRendererFunctions::DirectBindTexture(0);
		shader->Unbind();
		fbuffer->Unbind();
	}

	void BindTextures() {
		fbuffer->BindTextures();
	}

	void UnbindTextures() {
		fbuffer->UnbindTextures();
	}

	uint32_t GetFinalTexture() const {
		return fbuffer->GetTexture(0);
	}

	virtual void Update() = 0;
};

#endif
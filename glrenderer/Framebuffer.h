#ifndef RENDERER_FRAMEBUFFER_H
#define RENDERER_FRAMEBUFFER_H
#include <lilib/EngineDefs.h>
#include <lilib/List.h>

class Framebuffer {
private:
	uint32_t fbo, width, height;
	liList<uint32_t> textures, renderbuffers;
public:
	Framebuffer(uint32_t width, uint32_t height);
	~Framebuffer();

	void Initialize();
	void Shutdown();
	void Bind();
	void Unbind();
	bool CheckStatus() const;
	void AddFloatColorTexture(int attachment = 0);
	void AddUByteColorTexture(int attachment = 0);
	void AddDepthStencilRenderbuffer();
	void AddDepthRenderbuffer();
	uint32_t GetTexture(int index) const;
	uint32_t GetRenderbuffer(int index) const;
	uint32_t GetWidth() const;
	uint32_t GetHeight() const;
	void DrawBuffers();
	void Blit(uint32_t dest);
	void BindTextures();
	void UnbindTextures();
	uint32_t GetID() const;
	liList<uint32_t> GetTextures() const;
};

#endif
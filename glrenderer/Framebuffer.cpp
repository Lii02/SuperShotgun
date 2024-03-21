#include "Framebuffer.h"
#include "Wrapper.h"
#include <platform/win32/Win32Header.h>

Framebuffer::Framebuffer(uint32_t width, uint32_t height)
{
	this->width = width;
	this->height = height;
	Initialize();
}

Framebuffer::~Framebuffer()
{
	Shutdown();
}

void Framebuffer::Initialize()
{
	glGenFramebuffers(1, &fbo);
}

void Framebuffer::Shutdown()
{
	glDeleteTextures(textures.Size(), &textures[0]);
	glDeleteRenderbuffers(renderbuffers.Size(), &renderbuffers[0]);
	glDeleteFramebuffers(1, &fbo);
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, width, height);
}

void Framebuffer::Unbind()
{
	glViewport(0, 0, Sys_GetWidth(), Sys_GetHeight());
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool Framebuffer::CheckStatus() const
{
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void Framebuffer::AddFloatColorTexture(int attachment)
{
	uint32_t ID;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_2D, ID, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	textures.Push(ID);
}

void Framebuffer::AddUByteColorTexture(int attachment)
{
	uint32_t ID;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_2D, ID, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	textures.Push(ID);
}

void Framebuffer::AddDepthStencilRenderbuffer()
{
	uint32_t ID;
	glGenRenderbuffers(1, &ID);
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ID);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	renderbuffers.Push(ID);
}

void Framebuffer::AddDepthRenderbuffer()
{
	uint32_t ID;
	glGenRenderbuffers(1, &ID);
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, ID);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	renderbuffers.Push(ID);
}

uint32_t Framebuffer::GetTexture(int index) const
{
	return textures[index];
}

uint32_t Framebuffer::GetRenderbuffer(int index) const
{
	return renderbuffers[index];
}

uint32_t Framebuffer::GetWidth() const
{
	return width;
}

uint32_t Framebuffer::GetHeight() const
{
	return height;
}

void Framebuffer::DrawBuffers()
{
	liList<GLenum> buffers;
	for (int i = 0; i < textures.Size(); i++) {
		buffers.Push(GL_COLOR_ATTACHMENT0 + i);
	}
	glDrawBuffers(buffers.Size(), &buffers[0]);
}

void Framebuffer::Blit(uint32_t dest)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dest);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void Framebuffer::BindTextures()
{
	for (int i = 0; i < textures.Size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
	}
}

void Framebuffer::UnbindTextures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t Framebuffer::GetID() const
{
	return fbo;
}

liList<uint32_t> Framebuffer::GetTextures() const
{
	return textures;
}
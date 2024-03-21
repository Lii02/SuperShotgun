#include "Skybox.h"
#include "Wrapper.h"
#include "VAO.h"
#include <lilib/List.h>

static uint32_t skybox_vao, skybox_vbo;

#define SIZE FLT_MAX

void Skybox::InitializeSkyboxGraphics()
{
	liList<float> vertices = { -SIZE, SIZE, -SIZE, -SIZE, -SIZE, -SIZE, SIZE, -SIZE, -SIZE, SIZE, -SIZE, -SIZE,
					SIZE, SIZE, -SIZE, -SIZE, SIZE, -SIZE,

					-SIZE, -SIZE, SIZE, -SIZE, -SIZE, -SIZE, -SIZE, SIZE, -SIZE, -SIZE, SIZE, -SIZE, -SIZE, SIZE, SIZE, -SIZE,
					-SIZE, SIZE,

					SIZE, -SIZE, -SIZE, SIZE, -SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, -SIZE, SIZE, -SIZE,
					-SIZE,

					-SIZE, -SIZE, SIZE, -SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, -SIZE, SIZE, -SIZE, -SIZE,
					SIZE,

					-SIZE, SIZE, -SIZE, SIZE, SIZE, -SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, SIZE, -SIZE, SIZE, SIZE, -SIZE, SIZE,
					-SIZE,

					-SIZE, -SIZE, -SIZE, -SIZE, -SIZE, SIZE, SIZE, -SIZE, -SIZE, SIZE, -SIZE, -SIZE, -SIZE, -SIZE, SIZE, SIZE,
					-SIZE, SIZE };

	skybox_vao = Renderer_GenerateVAO();
	Renderer_BindVAO(skybox_vao);
	glGenBuffers(1, &skybox_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, skybox_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.Allocated(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Renderer_BindVAO(0);
}

void Skybox::ShutdownSkyboxGraphics()
{
	glDeleteBuffers(1, &skybox_vbo);
	Renderer_DeleteVAO(&skybox_vao);
}

Skybox::Skybox(RenderShader* shader, Texture3D* cubemap)
{
	this->shader = shader;
	this->cubemap = cubemap;
}

void Skybox::Draw()
{
	shader->Bind();
	cubemap->Bind();
	Renderer_BindVAO(skybox_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Renderer_BindVAO(0);
	cubemap->Unbind();
	shader->Unbind();
}
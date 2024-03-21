#include "ScreenQuad.h"
#include "Wrapper.h"
#include "VAO.h"
#include <lilib/List.h>
#include "MiscFunctions.h"

ScreenQuad* ScreenQuad::Instance = nullptr;

ScreenQuad::ScreenQuad()
{
	Initialize();
}

ScreenQuad::~ScreenQuad()
{
	Shutdown();
}

void ScreenQuad::Initialize()
{
	this->vao = Renderer_GenerateVAO();
	glGenBuffers(2, &vbo);
	liList<float> vertices = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f,
	};

	liList<int> indices = {
		1, 2, 0, 1, 3, 2,
	};

	Renderer_BindVAO(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.Allocated(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.Allocated(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	Renderer_BindVAO(0);
}

void ScreenQuad::Shutdown()
{
	glDeleteBuffers(2, &vbo);
	Renderer_DeleteVAO(&vao);
}

void ScreenQuad::Draw()
{
	MiscRendererFunctions::Prepare2D();
	Renderer_BindVAO(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	Renderer_BindVAO(0);
	MiscRendererFunctions::Close2D();
}
#include "GUIGraphics.h"
#include "Wrapper.h"
#include "VAO.h"
#include <lilib/List.h>

static uint32_t gui_vao, gui_vbo, gui_ibo, gui_tbo;

void GUIGraphics::Initialize()
{
	gui_vao = Renderer_GenerateVAO();
	glGenBuffers(3, &gui_vbo);
	liList<float> vertices = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f,
	};
	liList<int> indices = {
		1, 2, 0, 1, 3, 2,
	};
	liList<float> texture_coords = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f
	};
	Renderer_BindVAO(gui_vao);
	glBindBuffer(GL_ARRAY_BUFFER, gui_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.Allocated(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, gui_tbo);
	glBufferData(GL_ARRAY_BUFFER, texture_coords.Allocated(), &texture_coords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gui_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.Allocated(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	Renderer_BindVAO(0);
}

void GUIGraphics::Shutdown()
{
	Renderer_DeleteVAO(&gui_vao);
	glDeleteBuffers(3, &gui_vbo);
}

void GUIGraphics::Draw(Texture2D* image)
{
	image->Bind();
	Renderer_BindVAO(gui_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gui_ibo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	Renderer_BindVAO(0);
	image->Unbind();
}
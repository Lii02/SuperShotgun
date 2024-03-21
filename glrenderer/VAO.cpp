#include "VAO.h"

vao_t Renderer_GenerateVAO()
{
	vao_t v;
	glGenVertexArrays(1, &v);
	return v;
}

void Renderer_DeleteVAO(vao_t* vao)
{
	glDeleteVertexArrays(1, vao);
}

void Renderer_BindVAO(vao_t v)
{
	glBindVertexArray(v);
}
#include "Sprite.h"
#include "Wrapper.h"
#include "VAO.h"

static uint32_t sprite_vao, sprite_vbo, sprite_ibo, sprite_tbo;

void Sprite::InitializeSpriteGraphics()
{
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
	sprite_vao = Renderer_GenerateVAO();
	Renderer_BindVAO(sprite_vao);
	glGenBuffers(3, &sprite_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, sprite_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.Allocated(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, sprite_tbo);
	glBufferData(GL_ARRAY_BUFFER, texture_coords.Allocated(), &texture_coords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.Allocated(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Renderer_BindVAO(0);
}

void Sprite::ShutdownSpriteGraphics()
{
	glDeleteBuffers(3, &sprite_vbo);
	Renderer_DeleteVAO(&sprite_vao);
}

Sprite::Sprite(Texture2D* image)
{
	this->image = image;
}

Sprite::~Sprite()
{
	if (image->IsCopied())
		delete image;
}

void Sprite::Draw()
{
	image->Bind();
	Renderer_BindVAO(sprite_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite_ibo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	Renderer_BindVAO(0);
	image->Unbind();
}

Texture2D* Sprite::GetImage()
{
	return image;
}

void Sprite::SetImage(Texture2D* image)
{
	this->image = image;
}
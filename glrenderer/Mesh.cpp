#include "Mesh.h"
#include "Wrapper.h"

Mesh::Mesh()
{
	Initialize();
}

Mesh::~Mesh()
{
	Delete();
}

void Mesh::SetData(const liList<float>& vertices, const liList<float>& textures, const liList<int>& indices, const liList<float>& normals, const liList<float>& tangents)
{
	this->vertices = vertices;
	this->textures = textures;
	this->indices = indices;
	this->normals = normals;
	this->tangents = tangents;

	Renderer_BindVAO(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.Allocated(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, textures.Allocated(), &textures[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, normals.Allocated(), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, ttbo);
	glBufferData(GL_ARRAY_BUFFER, tangents.Allocated(), &tangents[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.Allocated(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	Renderer_BindVAO(0);
}

void Mesh::Initialize()
{
	this->vao = Renderer_GenerateVAO();
	glGenBuffers(5, &vbo);
}

void Mesh::Delete()
{
	Renderer_DeleteVAO(&vao);
	glDeleteBuffers(5, &vbo);
}

void Mesh::Draw()
{
	Renderer_BindVAO(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, indices.Size(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	Renderer_BindVAO(0);
}

void Mesh::SetFileData(bool from_file, liString filepath)
{
	this->from_file = from_file;
	this->filepath = filepath;
}

bool Mesh::IsFromFile() const
{
	return from_file;
}

liString Mesh::GetFilepath() const
{
	return filepath;
}
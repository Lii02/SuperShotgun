#ifndef RENDERER_MESH_H
#define RENDERER_MESH_H
#include "lilib/EngineDefs.h"
#include "VAO.h"
#include <lilib/List.h>
#include <lilib/LiString.h>

typedef unsigned int buffer_object_t;

class Mesh {
private:
	vao_t vao;
	buffer_object_t vbo, ibo, tbo, nbo, ttbo;

	liList<float> vertices, textures, normals, tangents;
	liList<int> indices;

	bool from_file;
	liString filepath;
public:
	Mesh();
	~Mesh();
	void SetData(const liList<float>& vertices, const liList<float>& textures, const liList<int>& indices, const liList<float>& normals, const liList<float>& tangents);
	void Initialize();
	void Delete();
	void Draw();

	void SetFileData(bool from_file, liString filepath);
	bool IsFromFile() const;
	liString GetFilepath() const;
};

#endif
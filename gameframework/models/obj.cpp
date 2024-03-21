#include "obj.h"

#define NO_INDEX -1

class PackedVertex {
public:
	liVector3f position;
	liVector2f uv;
	liVector3f normal;
	PackedVertex* duplicate = NULL;
	float length;
	int texture_index = NO_INDEX;
	int normal_index = NO_INDEX;
	int index;
	liList<liVector3f> tangents;
	liVector3f averaged_tangent;

	PackedVertex() = default;

	PackedVertex(liVector3f position, int index) {
		this->position = position;
		this->index = index;
		this->length = position.Length();
	}

	bool IsSet() const {
		return texture_index != NO_INDEX && normal_index != NO_INDEX;
	}

	bool HasSameTextureAndNormal(int texture_index_other, int normal_index_other) {
		return texture_index_other == texture_index && normal_index_other == normal_index;
	}

	void AverageTangents() {
		if (tangents.Size() == 0) {
			return;
		}
		for (size_t i = 0; i < tangents.Size(); i++) {
			averaged_tangent = averaged_tangent + tangents[i];
		}
		averaged_tangent.Normalize();
	}
};

PackedVertex* DealWithAlreadyProcessedVertex(PackedVertex* previous_vertex, int new_texture, int new_normal,
	liList<int>* indices, liList<PackedVertex*>* vertices) {
	if (previous_vertex->HasSameTextureAndNormal(new_texture, new_normal)) {
		indices->Push(previous_vertex->index);
		return previous_vertex;
	} else {
		PackedVertex* duplicate_vertex = new PackedVertex(previous_vertex->position, vertices->Size());
		duplicate_vertex->texture_index = new_texture;
		duplicate_vertex->normal_index = new_normal;
		previous_vertex->duplicate = duplicate_vertex;
		vertices->Push(duplicate_vertex);
		indices->Push(duplicate_vertex->index);
		return duplicate_vertex;
	}
}

PackedVertex* ProcessVertex(unsigned int* vertex, liList<PackedVertex*>* vertices, liList<int>* indices) {
	long index = vertex[0] - 1;
	PackedVertex* current_vertex = vertices->At(index);
	long texture_index = vertex[1] - 1;
	long normal_index = vertex[2] - 1;
	if (!current_vertex->IsSet()) {
		current_vertex->texture_index = texture_index;
		current_vertex->normal_index = normal_index;
		indices->Push(index);
		return current_vertex;
	} else {
		return DealWithAlreadyProcessedVertex(current_vertex, texture_index, normal_index, indices, vertices);
	}
}

void RemoveUnusedVertices(liList<PackedVertex*>* vertices) {
	for (unsigned int i = 0; i < vertices->Size(); i++) {
		vertices->At(i)->AverageTangents();
		if (!vertices->At(i)->IsSet()) {
			vertices->At(i)->texture_index = 0;
			vertices->At(i)->normal_index = 0;
		}
	}
}

void CalculateTangents(PackedVertex* v0, PackedVertex* v1, PackedVertex* v2, liList<liVector2f>* textures) {
	liVector3f deltaPos1 = liVector3f(v1->position.x - v0->position.x, v1->position.y - v0->position.y, v1->position.z - v0->position.z);
	liVector3f deltaPos2 = liVector3f(v2->position.x - v0->position.x, v2->position.y - v0->position.y, v2->position.z - v0->position.z);
	liVector2f uv0 = textures->At(v0->texture_index);
	liVector2f uv1 = textures->At(v1->texture_index);
	liVector2f uv2 = textures->At(v2->texture_index);
	liVector2f deltaUv1 = liVector2f(uv1.x - uv0.x, uv1.y - uv0.y);
	liVector2f deltaUv2 = liVector2f(uv2.x - uv0.x, uv2.y - uv0.y);

	float r = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
	deltaPos1 *= liVector3f(deltaUv2.y, deltaUv2.y, deltaUv2.y);
	deltaPos2 *= liVector3f(deltaUv1.y, deltaUv1.y, deltaUv1.y);
	liVector3f tangent = liVector3f(deltaPos1.x - deltaPos2.x, deltaPos1.y - deltaPos2.y, deltaPos1.z - deltaPos2.z);
	tangent *= liVector3f(r, r, r);
	v0->tangents.Push(tangent);
	v1->tangents.Push(tangent);
	v2->tangents.Push(tangent);
}

void ConvertToArrays(liList<PackedVertex*>& vertices, liList<liVector3f>& normals, liList<liVector2f>& textures,
	liList<float>& nvertices, liList<float>& nnormals, liList<float>& ntextures, liList<float>& tangents)
{
	for (int i = 0; i < vertices.Size(); i++) {
		PackedVertex* current = vertices[i];
		liVector3f position = current->position;
		liVector2f textureCoord = textures[current->texture_index];
		liVector3f normalVector = normals[current->normal_index];
		liVector3f tangent = current->averaged_tangent;
		
		nvertices[i * 3] = position.x;
		nvertices[i * 3 + 1] = position.y;
		nvertices[i * 3 + 2] = position.z;
		ntextures[i * 2] = textureCoord.x;
		ntextures[i * 2 + 1] = 1 - textureCoord.y;
		nnormals[i * 3] = normalVector.x;
		nnormals[i * 3 + 1] = normalVector.y;
		nnormals[i * 3 + 2] = normalVector.z;
		tangents[i * 3] = tangent.x;
		tangents[i * 3 + 1] = tangent.y;
		tangents[i * 3 + 2] = tangent.z;
	}
}

liOBJ* liOBJ::Parse(liFile* file)
{
	liOBJ* obj = new liOBJ(file);
	liOBJOutput* output = obj->output;
	auto lines = file->Read().Tokenize('\n');

	liList<PackedVertex*> pvertices;
	liList<liVector3f> normals;
	liList<liVector2f> uvs;
	liList<int> indices;

	for (size_t i = 0; i < lines.Size(); i++) {
		cstring line = lines[i]->c_str();
		char header[128];
		sscanf(line, "%s", header);
		if (!strcmp(header, "v")) {
			liVector3f vec;
			sscanf(line, "%s %f %f %f\n", header, &vec.x, &vec.y, &vec.z);
			pvertices.Push(new PackedVertex(vec, pvertices.Size()));
		} else if (!strcmp(header, "vt")) {
			liVector2f vec;
			sscanf(line, "%s %f %f\n", header, &vec.x, &vec.y);
			uvs.Push(vec);
		} else if (!strcmp(header, "vn")) {
			liVector3f vec;
			sscanf(line, "%s %f %f %f\n", header, &vec.x, &vec.y, &vec.z);
			normals.Push(vec);
		} else if (!strcmp(header, "f")) {
			unsigned int vertex_index[3], uv_index[3], normal_index[3];
			sscanf(line, "%s %d/%d/%d %d/%d/%d %d/%d/%d\n", header, &vertex_index[0], &uv_index[0], &normal_index[0], &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2]);

			unsigned int vertex1[3];
			vertex1[0] = vertex_index[0];
			vertex1[1] = uv_index[0];
			vertex1[2] = normal_index[0];
			auto v0 = ProcessVertex(vertex1, &pvertices, &indices);

			unsigned int vertex2[3];
			vertex2[0] = vertex_index[1];
			vertex2[1] = uv_index[1];
			vertex2[2] = normal_index[1];
			auto v1 = ProcessVertex(vertex2, &pvertices, &indices);

			unsigned int vertex3[3];
			vertex3[0] = vertex_index[2];
			vertex3[1] = uv_index[2];
			vertex3[2] = normal_index[2];
			auto v2 = ProcessVertex(vertex3, &pvertices, &indices);

			CalculateTangents(v0, v1, v2, &uvs);
		}
	}

	lines.DeleteDataPointers();

	RemoveUnusedVertices(&pvertices);
	size_t new_vsize = pvertices.Size() * 3;
	size_t new_uvsize = pvertices.Size() * 2;

	liList<float> new_vertices = liList<float>(new_vsize);	
	liList<float> new_normals = liList<float>(new_vsize);
	liList<float> new_tangents = liList<float>(new_vsize);
	liList<float> new_uvs = liList<float>(new_uvsize);
	
	ConvertToArrays(pvertices, normals, uvs, new_vertices, new_normals, new_uvs, new_tangents);
	output->vertices = new_vertices;
	output->indices = indices;
	output->textures = new_uvs;
	output->normals = new_normals;
	output->tangents = new_tangents;

	pvertices.DeleteDataPointers();
	return obj;
}

liOBJ::liOBJ(liFile* fileptr) : liAsset(fileptr)
{
	this->output = new liOBJOutput;
}

liOBJ::~liOBJ()
{
	delete output;
}

liOBJOutput* liOBJ::GetOutput()
{
	return output;
}

Mesh* liOBJ::ToMesh()
{
	Mesh* mesh = new Mesh();
	mesh->SetData(output->vertices, output->textures, output->indices, output->normals, output->tangents);
	mesh->SetFileData(true, fileptr->GetShortPath());
	return mesh;
}
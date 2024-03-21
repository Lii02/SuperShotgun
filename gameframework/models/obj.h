#ifndef FRAMEWORK_OBJ_H
#define FRAMEWORK_OBJ_H
#include <lilib/math/MathTypes.h>
#include <lilib/Map.h>
#include <gameframework/File.h>
#include <gameframework/Asset.h>
#include <glrenderer/Mesh.h>

struct liOBJOutput {
	liList<float> vertices, textures, normals, tangents;
	liList<int> indices;
};

class liOBJ : public liAsset {
private:
	liOBJOutput* output;
public:
	static liOBJ* Parse(liFile* file);

	liOBJ(liFile* fileptr);
	~liOBJ();
	liOBJOutput* GetOutput();
	Mesh* ToMesh();
};

#endif
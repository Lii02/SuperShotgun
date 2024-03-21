#ifndef ACTOR3D_H
#define ACTOR3D_H
#include "Actor.h"
#include "Material.h"
#include <glrenderer/Mesh.h>

class liActor3D : public liActor {
protected:
	Mesh* mesh;
	liMaterial* material;
public:
	liActor3D();
	~liActor3D();

	virtual void Spawn() override;
	virtual void Shutdown() override;
	virtual void Render(RenderShader* shader)override;
	virtual void Update() override;

	liMaterial* GetMaterial();
	void SetMaterial(liMaterial* new_material);
	Mesh* GetMesh();
	void SetMesh(Mesh* new_mesh);
};

#endif
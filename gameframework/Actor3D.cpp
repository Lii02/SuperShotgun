#include "Actor3D.h"
#include "Profiler.h"

liActor3D::liActor3D()
	: liActor(liActorType::TYPE_ACTOR3D, liActorFlag::FLAG_3D)
{
}

liActor3D::~liActor3D()
{
	Shutdown();
}

void liActor3D::Spawn()
{
	liActor::Spawn();
	this->material = new liMaterial();
	this->mesh = new Mesh();
}

void liActor3D::Shutdown()
{
	liActor::Shutdown();
	delete material;
	delete mesh;
}

void liActor3D::Update()
{
	liActor::Update();
}

void liActor3D::Render(RenderShader* shader)
{
	liActor::Render(shader);
	material->Bind(shader);
	LoadTransform(shader->GetProgram());
	mesh->Draw();
	material->Unbind(shader);
}

Mesh* liActor3D::GetMesh()
{
	return mesh;
}

void liActor3D::SetMesh(Mesh* new_mesh)
{
	delete mesh;
	this->mesh = new_mesh;
}

void liActor3D::SetMaterial(liMaterial* new_material)
{
	delete material;
	this->material = new_material;
}

liMaterial* liActor3D::GetMaterial()
{
	return material;
}
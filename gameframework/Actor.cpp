#include "Actor.h"
#include <lilib/GUID.h>

liActor::liActor(liActorType type, liActorFlag flag)
{
	this->type = type;
	this->flag = flag;
	this->tag = "UnnamedActor";
	this->parent = NULL;
	this->GUID = LiLib_GenerateGUID();
	Show();
}

liActor::~liActor()
{
	Shutdown();
}

void liActor::Show()
{
	this->active = true;
}

void liActor::Hide()
{
	this->active = false;
}

void liActor::SetActive(bool active)
{
	this->active = active;
}

bool liActor::IsActive() const
{
	return active;
}

liString liActor::GetTag() const
{
	return tag;
}

void liActor::SetTag(liString tag)
{
	this->tag = tag;
}

liList<liActor*>* liActor::GetChildren()
{
	return &children;
}

liActor* liActor::AddChild(liActor* child)
{
	child->parent = this;
	child->Spawn();
	children.Push(child);
	return child;
}

liActor* liActor::GetChildren(int index)
{
	return children[index];
}

liActorType liActor::GetType() const
{
	return type;
}

liString liActor::GetGUID() const
{
	return GUID;
}

void liActor::SetGUID(liString new_guid)
{
	this->GUID = new_guid;
}

void liActor::LoadTransform(ShaderProgram* program)
{
	if (parent != NULL) {
		program->LoadMat4x4("transform", transform.ToRelativeMatrix(parent->transform));
	} else {
		program->LoadMat4x4("transform", transform.ToTransformMatrix());
	}
}

liActorFlag liActor::GetFlag() const
{
	return flag;
}

void liActor::Spawn()
{
	for (size_t i = 0; i < children.Size(); i++) {
		children[i]->Spawn();
	}
}

void liActor::Shutdown()
{
	children.DeleteDataPointers();
}

void liActor::Render(RenderShader* shader)
{
	for (size_t i = 0; i < children.Size(); i++) {
		children[i]->Render(shader);
	}
}

void liActor::Update()
{
	for (size_t i = 0; i < children.Size(); i++) {
		children[i]->Update();
	}
}
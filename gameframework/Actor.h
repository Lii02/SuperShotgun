#ifndef ACTOR_H
#define ACTOR_H
#include "Object.h"
#include <lilib/EngineDefs.h>
#include <lilib/LiString.h>
#include <glrenderer/ShaderProgram.h>
#include "Transform.h"
#include "FrameworkEnums.h"

class liActor : public IObject {
protected:
	liString tag;
	bool active;
	liActorType type = liActorType::TYPE_ACTOR;
	liActorFlag flag;
	liList<liActor*> children;
	liString GUID;
	liActor* parent;
public:
	liTransform transform;

	liActor(liActorType type, liActorFlag flag);
	virtual ~liActor();

	void Show();
	void Hide();
	void SetActive(bool active);
	bool IsActive() const;
	liString GetTag() const;
	void SetTag(liString tag);
	liList<liActor*>* GetChildren();
	liActor* AddChild(liActor* child);
	liActor* GetChildren(int index);
	liActorType GetType() const;
	liString GetGUID() const;
	void SetGUID(liString new_guid);
	void LoadTransform(ShaderProgram* program);
	liActorFlag GetFlag() const;

	virtual void Spawn() override;
	virtual void Shutdown() override;
	virtual void Render(RenderShader* shader) override;
	virtual void Update() override;
};

#endif
#ifndef FRAMEWORK_ACTOR2D_H
#define FRAMEWORK_ACTOR2D_H
#include <lilib/EngineDefs.h>
#include <glrenderer/Sprite.h>
#include <glrenderer/RenderShader.h>
#include "Actor.h"

class liActor2D : public liActor {
private:
	Sprite* sprite;
	RenderShader* shader;
public:
	liActor2D();
	~liActor2D();
	
	Sprite* GetSprite();
	void SetImage(Texture2D* image);
	void SetShader(RenderShader* shader);

	virtual void Spawn() override;
	virtual void Shutdown() override;
	virtual void Render(RenderShader* shader)override;
	virtual void Update() override;
};

#endif
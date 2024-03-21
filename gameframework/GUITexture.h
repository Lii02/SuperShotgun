#ifndef FRAMEWORK_GUITEXTURE_H
#define FRAMEWORK_GUITEXTURE_H
#include <lilib/EngineDefs.h>
#include <glrenderer/Texture2D.h>
#include <glrenderer/RenderShader.h>
#include "Actor.h"

class liGUITexture : public liActor {
private:
	Texture2D* image;
public:
	liVector3f tint;

	liGUITexture(Texture2D* image, liVector3f tint = liVector3f(0, 0, 0));
	~liGUITexture();

	virtual void Spawn() override;
	virtual void Shutdown() override;
	virtual void Render(RenderShader* shader) override;
	virtual void Update() override;

	Texture2D* GetImage();
	void SetImage(Texture2D* texture);
};

#endif
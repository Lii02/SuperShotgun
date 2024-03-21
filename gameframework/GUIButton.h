#ifndef GAMEFRAMEWORK_GUIBUTTON_H
#define GAMEFRAMEWORK_GUIBUTTON_H
#include <lilib/EngineDefs.h>
#include "GUITexture.h"
#include "Label.h"
#include "Actor.h"

class liGUIButton : public liActor {
private:
	liLabel* label;
	liGUITexture* texture;
public:
	liGUIButton(liTTF* font, Texture2D* image, liString text, liVector4f color);
	~liGUIButton();

	virtual void Spawn() override;
	virtual void Shutdown() override;
	virtual void Render(RenderShader* shader) override;
	virtual void Update() override;

	bool OnClick() const;
};

#endif
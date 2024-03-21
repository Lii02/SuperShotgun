#ifndef FRAMEWORK_LABEL_H
#define FRAMEWORK_LABEL_H
#include <lilib/EngineDefs.h>
#include <lilib/LiString.h>
#include <glrenderer/RenderShader.h>
#include <lilib/math/Matrices.h>
#include "Actor.h"
#include "FrameworkStructs.h"
#include "fonts/ttf.h"

#define LABEL_DEFAULT_KERNING 6

class liLabel : public liActor {
private:
	liTTF* font;
public:
	liString text;
	int kerning;
	liVector4f color;

	liLabel(liTTF* font, liString text, liVector4f color, int kerning = LABEL_DEFAULT_KERNING);
	~liLabel();

	virtual void Spawn() override;
	virtual void Shutdown() override;
	virtual void Render(RenderShader* shader) override;
	virtual void Update() override;
	
	liTTF* GetFont();
	float GetLabelWidth();
};

#endif
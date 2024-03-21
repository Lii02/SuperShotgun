#ifndef FRAMEWORK_LIGHT_H
#define FRAMEWORK_LIGHT_H
#include <lilib/EngineDefs.h>
#include "Actor.h"

enum liLightType : ubyte {
	TYPE_POINT = 0,
	TYPE_SPOTLIGHT = 1,
	TYPE_DIRECTIONAL = 2,
};

class liLight : public liActor {
public:
	liLightType type;
	liVector3f color;
	float intensity, linear, quadratic, radius, cutoff;

	liLight(liLightType type, liVector3f color, float intensity, float radius = 10, float linear = 0, float quadratic = 1, float cutoff = 0);

	virtual void Spawn() override;
	virtual void Shutdown() override;
	virtual void Render(RenderShader* shader) override;
	virtual void Update() override;
};

#endif
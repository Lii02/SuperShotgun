#ifndef LIGHTING_ENGINE_H
#define LIGHTING_ENGINE_H
#include <lilib/EngineDefs.h>
#include <lilib/List.h>
#include "Material.h"
#include "Light.h"

#define MAX_LIGHTS 1

class liLightingEngine {
private:
public:
	static void LoadLighting(RenderShader* shader, liList<liLight*>* lights, liVector3f view_position);
};

#endif
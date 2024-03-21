#ifndef OBJECT_H
#define OBJECT_H
#include <lilib/EngineDefs.h>
#include <glrenderer/RenderShader.h>

class IObject {
public:
	virtual ~IObject() {}

	virtual void Spawn() = 0;
	virtual void Shutdown() = 0;
	virtual void Render(RenderShader* shader) = 0;
	virtual void Update() = 0;
};

#endif
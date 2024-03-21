#ifndef RENDERER_SCREENQAUAD_H
#define RENDERER_SCREENQAUAD_H
#include <lilib/EngineDefs.h>

class ScreenQuad {
private:
	uint32_t vao, vbo, ibo;
public:
	static ScreenQuad* Instance;

	ScreenQuad();
	~ScreenQuad();
	void Initialize();
	void Shutdown();
	void Draw();
};

#endif
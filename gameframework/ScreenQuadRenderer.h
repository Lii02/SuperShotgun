#ifndef GAMEFRAMEWORK_SCREENQUADFRAMEWORK_H
#define GAMEFRAMEWORK_SCREENQUADFRAMEWORK_H
#include <lilib/EngineDefs.h>
#include <glrenderer/RenderShader.h>
#include <gameframework/ContentManager.h>

class ScreenQuadRenderer {
private:
	RenderShader* quadshader;
public:
	ScreenQuadRenderer(liContentManager* content);
	~ScreenQuadRenderer();

	void Initialize(liContentManager* content);
	void Shutdown();
	void Present();
};

#endif
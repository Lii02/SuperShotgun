#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H
#include <lilib/EngineDefs.h>
#include "ShaderProgram.h"
#include <lilib/LiString.h>

class RenderShader {
private:
	ShaderProgram* program;
	uint32_t vertexID, fragmentID;
public:
	RenderShader();
	~RenderShader();

	void Initialize(liList<cstring> attribs, cstring vertex_src, cstring fragment_src);
	void Delete();
	void Bind();
	void Unbind();

	ShaderProgram* GetProgram();
};

#endif
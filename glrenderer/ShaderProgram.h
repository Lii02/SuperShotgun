#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <lilib/EngineDefs.h>
#include <lilib/math/MathTypes.h>
#include <lilib/math/Matrices.h>

class ShaderProgram {
private:
	uint32_t ID;
public:
	ShaderProgram();
	~ShaderProgram();

	void Bind();
	void Unbind();
	void Initialize();
	void Delete();
	void Finish();
	uint32_t GetID();
	uint32_t GetUniformLocation(cstring tag) const;
	void LoadInt(cstring tag, int v);
	void LoadFloat(cstring tag, float v);
	void LoadVec2f(cstring tag, liVector2f v);
	void LoadVec3f(cstring tag, liVector3f v);
	void LoadVec4f(cstring tag, liVector4f v);
	void LoadMat4x4(cstring tag, liMatrix4x4 v);
	static uint32_t CreateShader(cstring src, uint32_t type, uint32_t program);
};

#endif
#include "ShaderProgram.h"
#include "Wrapper.h"

ShaderProgram::ShaderProgram()
{
	Initialize();
}

ShaderProgram::~ShaderProgram()
{
	Delete();
}

void ShaderProgram::Bind()
{
	glUseProgram(ID);
}

void ShaderProgram::Unbind()
{
	glUseProgram(0);
}

void ShaderProgram::Initialize()
{
	this->ID = glCreateProgram();
}

void ShaderProgram::Delete()
{
	Unbind();
	glDeleteProgram(ID);
}

void ShaderProgram::Finish()
{
	glValidateProgram(ID);
	glLinkProgram(ID);

	/*int status;
	glGetProgramiv(ID, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE) {
		int info_length;
		glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &info_length);
		char* info_log = new char[info_length];
		glGetProgramInfoLog(ID, info_length, NULL, info_log);
		printf("%s\n", info_log);
		delete[] info_log;
	}*/
}

uint32_t ShaderProgram::GetID()
{
	return ID;
}

uint32_t ShaderProgram::GetUniformLocation(cstring tag) const
{
	return glGetUniformLocation(ID, tag);
}

void ShaderProgram::LoadInt(cstring tag, int v)
{
	glUniform1i(GetUniformLocation(tag), v);
}

void ShaderProgram::LoadFloat(cstring tag, float v)
{
	glUniform1f(GetUniformLocation(tag), v);
}

void ShaderProgram::LoadVec2f(cstring tag, liVector2f v)
{
	glUniform2f(GetUniformLocation(tag), v.x, v.y);
}

void ShaderProgram::LoadVec3f(cstring tag, liVector3f v)
{
	glUniform3f(GetUniformLocation(tag), v.x, v.y, v.z);
}

void ShaderProgram::LoadVec4f(cstring tag, liVector4f v)
{
	glUniform4f(GetUniformLocation(tag), v.x, v.y, v.z, v.w);
}

void ShaderProgram::LoadMat4x4(cstring tag, liMatrix4x4 v)
{
	glUniformMatrix4fv(GetUniformLocation(tag), 1, GL_FALSE, &v[0][0]);
}

uint32_t ShaderProgram::CreateShader(cstring src, uint32_t type, uint32_t program)
{
	uint32_t shader = glCreateShader(type);
	size_t len = strlen(src);
	glShaderSource(shader, 1, &src, (int*)&len);
	glCompileShader(shader);
	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		int info_length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);
		char* info_log = new char[info_length];
		glGetShaderInfoLog(shader, info_length, NULL, info_log);
		printf("%s\n", info_log);
		delete[] info_log;
	}
	glAttachShader(program, shader);
	return shader;
}
#include "RenderShader.h"
#include "Wrapper.h"

RenderShader::RenderShader()
{
}

RenderShader::~RenderShader()
{
	Delete();
}

void RenderShader::Initialize(liList<cstring> attribs, cstring vertex_src, cstring fragment_src)
{
	this->program = new ShaderProgram();
	this->vertexID = ShaderProgram::CreateShader(vertex_src, GL_VERTEX_SHADER, program->GetID());
	this->fragmentID = ShaderProgram::CreateShader(fragment_src, GL_FRAGMENT_SHADER, program->GetID());
	
	for (int i = 0; i < attribs.Size(); i++) {
		glBindAttribLocation(program->GetID(), i, attribs[i]);
	}

	program->Finish();
}

void RenderShader::Delete()
{
	glDetachShader(program->GetID(), vertexID);
	glDeleteShader(vertexID);
	glDetachShader(program->GetID(), fragmentID);
	glDeleteShader(fragmentID);
	delete program;
}

void RenderShader::Bind()
{
	program->Bind();
}

void RenderShader::Unbind()
{
	program->Unbind();
}

ShaderProgram* RenderShader::GetProgram()
{
	return program;
}
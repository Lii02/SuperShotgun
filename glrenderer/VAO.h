#ifndef RENDERER_VAO_H
#define RENDERER_VAO_H
#include "Wrapper.h"

typedef unsigned int vao_t;

vao_t Renderer_GenerateVAO();
void Renderer_DeleteVAO(vao_t* vao);
void Renderer_BindVAO(vao_t v);

#endif
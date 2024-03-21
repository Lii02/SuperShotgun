#include "LightingEngine.h"
#include <lilib/math/MathHelper.h>

void liLightingEngine::LoadLighting(RenderShader* shader, liList<liLight*>* lights, liVector3f view_position)
{
	shader->Bind();
	ShaderProgram* program = shader->GetProgram();
	program->LoadVec3f("view_position", view_position);
	for (int i = 0; i < lights->Size(); i++) {
		liLight* light = lights->At(i);
		if (light->IsActive()) {
			program->LoadInt((liString("lights[") + liString::IntToString(i) + "].type").c_str(), (int)light->type);
			program->LoadFloat((liString("lights[") + liString::IntToString(i) + "].intensity").c_str(), light->intensity);
			program->LoadVec3f((liString("lights[") + liString::IntToString(i) + "].position").c_str(), light->transform.position);
			program->LoadVec3f((liString("lights[") + liString::IntToString(i) + "].direction").c_str(), liMathHelper::VectorToRadians(light->transform.rotation));
			program->LoadVec3f((liString("lights[") + liString::IntToString(i) + "].color").c_str(), light->color);
			program->LoadFloat((liString("lights[") + liString::IntToString(i) + "].linear").c_str(), light->linear);
			program->LoadFloat((liString("lights[") + liString::IntToString(i) + "].quadratic").c_str(), light->quadratic);
			program->LoadFloat((liString("lights[") + liString::IntToString(i) + "].cutoff").c_str(), liMathHelper::ToRadians(light->cutoff));
			program->LoadFloat((liString("lights[") + liString::IntToString(i) + "].radius").c_str(), light->radius);
		}
	}
	shader->Unbind();
}
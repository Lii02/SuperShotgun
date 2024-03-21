#include "Material.h"

#define MATERIAL_VALUE_COUNT 2

liMaterial::liMaterial()
{
	this->values[LIMATERIAL_DIFFUSE_UNIT] = new liMaterialValue(liVector3f(0, 0, 0));
	this->values[LIMATERIAL_SPECULAR_UNIT] = new liMaterialValue(0.0f);
	this->nmap = new liMaterialNormalMap();
}

liMaterial::~liMaterial()
{
	for (int i = 0; i < MATERIAL_VALUE_COUNT; i++) {
		delete values[i];
	}
	delete nmap;
}

void liMaterial::Bind(RenderShader* gbuffer_shader)
{
	for (int i = 0; i < MATERIAL_VALUE_COUNT; i++) {
		values[i]->SetIndex(i);
		values[i]->Bind(gbuffer_shader);
	}
	nmap->Bind(gbuffer_shader);
}

void liMaterial::Unbind(RenderShader* gbuffer_shader)
{
	nmap->Unbind(gbuffer_shader);
	for (int i = 0; i < MATERIAL_VALUE_COUNT; i++) {
		values[i]->Unbind(gbuffer_shader);
	}
}

liMaterialValue* liMaterial::GetValue(ubyte index)
{
	return values[index];
}

void liMaterial::SetValue(ubyte index, liMaterialValue* new_value)
{
	delete values[index];
	this->values[index] = new_value;
}

liMaterialNormalMap* liMaterial::GetNormalMap()
{
	return nmap;
}

void liMaterial::SetNormalMap(liMaterialNormalMap* new_nmap)
{
	delete nmap;
	this->nmap = new_nmap;
}

liMaterialValue::liMaterialValue(liVector3f color)
{
	this->color = color;
	this->type = liMaterialValueType::TYPE_COLOR;
}

liMaterialValue::liMaterialValue(float value)
{
	this->color.x = value;
	this->type = liMaterialValueType::TYPE_FLOAT;
}

liMaterialValue::liMaterialValue(Texture2D* texture)
{
	this->texture = texture;
	this->type = liMaterialValueType::TYPE_TEXTURE;
}

liMaterialValue::~liMaterialValue()
{
	if (type == liMaterialValueType::TYPE_TEXTURE && texture)
		delete texture;
}

void liMaterialValue::SetIndex(ubyte index)
{
	this->index = index;
}

void liMaterialValue::Bind(RenderShader* shader)
{
	liString full_tag = "mat.";
	full_tag.Append(liString("values[") + liString::IntToString(index) + liString("]."));

	shader->GetProgram()->LoadInt((full_tag + "type").c_str(), type);
	switch (type) {
	case liMaterialValueType::TYPE_COLOR:
		shader->GetProgram()->LoadVec3f((full_tag + "color").c_str(), color);
		break;
	case liMaterialValueType::TYPE_FLOAT:
		shader->GetProgram()->LoadVec3f((full_tag + "color").c_str(), color);
		break;
	case liMaterialValueType::TYPE_TEXTURE:
		texture->Bind(index);
		shader->GetProgram()->LoadInt((full_tag + "texture_sampler").c_str(), index);
		break;
	}
}

void liMaterialValue::Unbind(RenderShader* shader)
{
	switch (type) {
	case liMaterialValueType::TYPE_TEXTURE:
		texture->Unbind();
		break;
	}
}

liMaterialNormalMap::liMaterialNormalMap(Texture2D* texture)
{
	this->texture = texture;
	this->uses_map = (texture != NULL);
}

liMaterialNormalMap::~liMaterialNormalMap()
{
	if (texture != NULL)
		delete texture;
}

void liMaterialNormalMap::Bind(RenderShader* shader)
{
	if (uses_map && texture != NULL) {
		texture->Bind(LIMATERIAL_NORMAL_UNIT);
		shader->GetProgram()->LoadInt("mat.nmap.uses_map", uses_map);
		shader->GetProgram()->LoadInt("mat.nmap.texture_sampler", LIMATERIAL_NORMAL_UNIT);
	}
}

void liMaterialNormalMap::Unbind(RenderShader* shader)
{
	if (uses_map && texture != NULL)
		texture->Unbind();
	shader->GetProgram()->LoadInt("mat.nmap.uses_map", false);
}
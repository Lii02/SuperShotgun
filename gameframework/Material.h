#ifndef MATERIAL_H
#define MATERIAL_H
#include <lilib/EngineDefs.h>
#include <glrenderer/RenderShader.h>
#include <glrenderer/Texture2D.h>

#define LIMATERIAL_DIFFUSE_UNIT 0
#define LIMATERIAL_SPECULAR_UNIT 1
#define LIMATERIAL_NORMAL_UNIT 4

enum liMaterialValueType : ubyte {
	TYPE_COLOR = 0,
	TYPE_TEXTURE = 1,
	TYPE_FLOAT = 2,
};

class liMaterialValue {
public:
	// If the type is a float, just use the R channel or something
	liVector3f color;
	Texture2D* texture;
	liMaterialValueType type;
	ubyte index;

	liMaterialValue() = default;
	liMaterialValue(liVector3f color);
	liMaterialValue(float value);
	liMaterialValue(Texture2D* texture);
	~liMaterialValue();

	void SetIndex(ubyte index);
	void Bind(RenderShader* shader);
	void Unbind(RenderShader* shader);
};

class liMaterialNormalMap {
public:
	Texture2D* texture;
	bool uses_map;

	liMaterialNormalMap(Texture2D* texture = NULL);
	~liMaterialNormalMap();
	void Bind(RenderShader* shader);
	void Unbind(RenderShader* shader);
};

class liMaterial {
private:
	liMaterialValue* values[4];
	liMaterialNormalMap* nmap;
public:
	liMaterial();
	~liMaterial();

	void Bind(RenderShader* gbuffer_shader);
	void Unbind(RenderShader* gbuffer_shader);

	liMaterialValue* GetValue(ubyte index);
	void SetValue(ubyte index, liMaterialValue* new_value);
	liMaterialNormalMap* GetNormalMap();
	void SetNormalMap(liMaterialNormalMap* new_nmap);
};

#endif
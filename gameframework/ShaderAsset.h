#ifndef FRAMEWORK_SHADER_ASSET_H
#define FRAMEWORK_SHADER_ASSET_H
#include <lilib/EngineDefs.h>
#include <glrenderer/RenderShader.h>
#include "Asset.h"

class liShaderAsset : public liAsset {
private:
	liString source;
public:
	liShaderAsset(liFile* file);
	liString* GetSource();
	void SetSource(liString new_source);

	static RenderShader* CreateShader(liShaderAsset* vertex, liShaderAsset* fragment, liList<cstring> attribs);
};

#endif
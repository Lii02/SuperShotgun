#ifndef SHADER_PREPROCESSOR_H
#define SHADER_PREPROCESSOR_H
#include <lilib/EngineDefs.h>
#include <lilib/LiString.h>
#include <gameframework/FileSystem.h>

class liShaderPreprocessor {
private:
public:
	static liString PreprocessShader(liString input, liFileSystem* fs);
};

#endif
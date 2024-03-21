#include "ShaderPreprocessor.h"

liString liShaderPreprocessor::PreprocessShader(liString input, liFileSystem* fs)
{
	liString output;
	auto lines = input.Tokenize('\n');

	for (auto it = lines.Begin(); it != lines.End(); it++) {
		auto line = **it;
		if (line.Contains("@include")) {
			char buff[0xFF] = {0};
			sscanf(line.c_str(), "@include %s", buff);
			liFile* file = fs->FindFile(buff);
			output.Append(file->Read());
			output.Append('\n');
			//PreprocessShader(output, fs);
		} else {
			output.Append(line);
			output.Append('\n');
		}
	}

	liString::CleanupTokenized(&lines);
	return output;
}
#ifndef GAMEFRAMEWORK_CONFIG_FILE_H
#define GAMEFRAMEWORK_CONFIG_FILE_H
#include <lilib/EngineDefs.h>
#include <lilib/Dictionary.h>
#include "FileSystem.h"

class ConfigFile {
private:
	liDictionary<liString, liString> values;
	liFile* file;
public:
	ConfigFile();
	~ConfigFile();
	liString GetValue(liString key);
	liFile* WriteFile(liString name, liFileSystem* fs);
	void AddValue(liString key, int value);
	void AddValue(liString key, bool value);
	void AddValue(liString key, float value);

	static ConfigFile* Parse(liFile* file);
};

#endif
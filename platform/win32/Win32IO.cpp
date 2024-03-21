#include "Win32Header.h"

void Sys_CreateFolder(cstring path) {
	CreateDirectoryA(path, NULL);
}

bool Sys_FolderExists(cstring name) {
	DWORD v = GetFileAttributesA(name);
	return (v != INVALID_FILE_ATTRIBUTES && (v & FILE_ATTRIBUTE_DIRECTORY));
}
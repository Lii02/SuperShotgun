#ifndef FRAMEWORK_FILESYSTEM_H
#define FRAMEWORK_FILESYSTEM_H
#include "File.h"
#include <lilib/List.h>

class liFileSystem {
	friend class liFile;
private:
	liList<liFile*> files;
	liList<liFileSystem*> folders;
	liString head;
public:
	liFileSystem(liString head);
	~liFileSystem();

	void Setup();
	void Close();
	liString GetHeadDirectory();
	liFile* FindFile(liString filename);
	liFile* AddFile(liString filename);
	liFileSystem* AddFolder(liString foldername);
	liFileSystem* FindFolder(liString foldername);
	liString GetCompletePath(liString path);
	static ubyte DetermineFlag(liString filename);
	liList<liFile*> GetFiles();
	liList<liFileSystem*> GetFolders();

	// Debug functions
	void PrintFS();
};

#endif
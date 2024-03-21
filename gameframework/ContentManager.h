#ifndef FRAMEWORK_CONTENT_MANAGER_H
#define FRAMEWORK_CONTENT_MANAGER_H
#include <lilib/EngineDefs.h>
#include "Asset.h"
#include <gameframework/FileSystem.h>
#include <lilib/List.h>

class liContentManager {
private:
	liList<liAsset*> assets;
	liFileSystem* fs;

	void ProcessAsset(liFile* file);
public:
	liContentManager(liFileSystem* fs);
	~liContentManager();
	void LoadContent();
	liAsset* GetAssetByName(liString name);
	liAsset* GetAssetByGUID(liString guid);
	template <typename T>
	T* GetAsset(liString name);
	template <typename T>
	T* LoadAsset(liString name);
};

template<typename T>
inline T* liContentManager::GetAsset(liString name)
{
	return (T*)GetAssetByName(name);
}

template<typename T>
inline T* liContentManager::LoadAsset(liString name)
{
	if (!GetAsset<T>(name)) {
		ProcessAsset(fs->FindFile(name));
		return GetAsset<T>(name);
	} else {
		return (T*)GetAssetByName(name);
	}
}

#endif
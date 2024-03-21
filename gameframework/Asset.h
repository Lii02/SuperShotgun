#ifndef FRAMEWORK_ASSET_H
#define FRAMEWORK_ASSET_H
#include <lilib/EngineDefs.h>
#include <lilib/GUID.h>
#include <gameframework/File.h>

class liAsset {
protected:
	liString guid;
	liString name;
	liFile* fileptr;
public:
	liAsset();
	liAsset(liFile* fileptr);
	virtual ~liAsset();

	liString GetGUID() const;
	liFile* GetFile() const;
	liString GetName() const;
	void SetName(liString name);
};

#endif
#include "Asset.h"
#include <lilib/GUID.h>

liAsset::liAsset()
{
    this->guid = LiLib_GenerateGUID();
}

liAsset::liAsset(liFile* fileptr)
{
    this->fileptr = fileptr;
    this->name = fileptr->GetCompletePath();
    this->guid = LiLib_GenerateGUID();
}

liAsset::~liAsset()
{
}

liString liAsset::GetGUID() const
{
    return guid;
}

liFile* liAsset::GetFile() const
{
    return fileptr;
}

liString liAsset::GetName() const
{
    return name;
}

void liAsset::SetName(liString name)
{
    this->name = name;
}
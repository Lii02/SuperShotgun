#include "ContentManager.h"
#include "models/obj.h"
#include "sound/wav.h"
#include "image/bmp.h"
#include "ShaderAsset.h"
#include "ShaderPreprocessor.h"
#include "Profiler.h"
#include <gameframework/fonts/ttf.h>

void liContentManager::ProcessAsset(liFile* file)
{
	if (file->GetCompletePath().Contains(".bmp")) {
		liBMP* bmp = liBMP::Load(file);
		assets.Push(bmp);
	} else if (file->GetCompletePath().Contains(".obj")) {
		liOBJ* obj = liOBJ::Parse(file);
		assets.Push(obj);
	} else if (file->GetCompletePath().Contains(".wav")) {
		liWAV* wav = liWAV::Load(file);
		assets.Push(wav);
	} else if (file->GetCompletePath().Contains(".vsh") || file->GetCompletePath().Contains(".fsh") || file->GetCompletePath().Contains(".glsl")) {
		liShaderAsset* shaderasset = new liShaderAsset(file);
		auto processed = liShaderPreprocessor::PreprocessShader(shaderasset->GetFile()->Read(), fs);
		shaderasset->SetSource(processed);
		assets.Push(shaderasset);
	} else if (file->GetCompletePath().Contains(".ttf")) {
		liTTF* ttf = liTTF::Load(file);
		assets.Push(ttf);
	}
}

liContentManager::liContentManager(liFileSystem* fs)
{
	this->fs = fs;
}

liContentManager::~liContentManager()
{
	assets.DeleteDataPointers();
}

void liContentManager::LoadContent()
{
	liProfiler::StartFunction("Content");
	auto files = fs->GetFiles();
	for (auto it = files.Begin(); it != files.End(); it++) {
		auto file = *it;
		ProcessAsset(file);
	}
	liProfiler::EndFunction();
}

liAsset* liContentManager::GetAssetByName(liString name)
{
	liFile* file = fs->FindFile(name);
	for (size_t i = 0; i < assets.Size(); i++) {
		auto asset = assets[i];
		if (assets[i]->GetName() == file->GetCompletePath())
			return assets[i];
	}
	return nullptr;
}

liAsset* liContentManager::GetAssetByGUID(liString guid)
{
	for (size_t i = 0; i < assets.Size(); i++) {
		if (assets[i]->GetGUID() == guid)
			return assets[i];
	}
	return nullptr;
}
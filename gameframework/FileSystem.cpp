#include "FileSystem.h"
#include <filesystem>
#include <iostream>
#include <platform/win32/Win32Header.h>
#include "Debug.h"

namespace fs = std::filesystem;

liFileSystem::liFileSystem(liString head)
{
	this->head = head;
	Setup();
}

liFileSystem::~liFileSystem()
{
	Close();
}

void liFileSystem::Setup()
{
	for (int i = 0; i < folders.Size(); i++) {
		folders[i]->Setup();
	}
	
	for (const auto& entry : fs::directory_iterator(head.c_str())) {
		auto path = entry.path().string();
		if (entry.is_directory()) {
			liFileSystem* fs = new liFileSystem(path.c_str());
			folders.Push(fs);
		} else if (entry.is_regular_file()) {
			liFile* file = new liFile(path.c_str(), path.substr(head.Length() + 1, path.length()).c_str(), LIFILE_READ);
			file->AddFlag(DetermineFlag(path.c_str()));
			files.Push(file);
		}
	}
}

void liFileSystem::Close()
{
	folders.DeleteDataPointers();
	files.DeleteDataPointers();
}

liString liFileSystem::GetHeadDirectory()
{
	return head;
}

liFile* liFileSystem::FindFile(liString filename)
{
	liString complete = GetCompletePath(filename);
	for (int i = 0; i < files.Size(); i++) {
		if (files[i]->complete_path == complete)
			return files[i];
	}

	for (int i = 0; i < folders.Size(); i++) {
		auto file = folders[i]->FindFile(filename);
		if (file)
			return file;
	}
	return nullptr;
}

liFile* liFileSystem::AddFile(liString filename)
{
	liFile* file = new liFile(GetCompletePath(filename), filename, LIFILE_WRITE);
	file->AddFlag(DetermineFlag(filename));
	files.Push(file);
	return file;
}

liFileSystem* liFileSystem::AddFolder(liString foldername)
{
	auto path = GetCompletePath(foldername);
	Sys_CreateFolder(path.c_str());
	liFileSystem* folder = new liFileSystem(path);
	folders.Push(folder);
	return folder;
}

liFileSystem* liFileSystem::FindFolder(liString foldername)
{
	auto complete = GetCompletePath(foldername);
	for (int i = 0; i < folders.Size(); i++) {
		if (folders[i]->head == complete)
			return folders[i];
	}

	for (int i = 0; i < folders.Size(); i++) {
		auto folder = folders[i]->FindFolder(foldername);
		if (folder) {
			return folder;
		}
	}
	return nullptr;
}

liString liFileSystem::GetCompletePath(liString path)
{
	liString connected_path = head;
	connected_path.Append('\\');
	connected_path.Append(path.c_str());
	return connected_path;
}

ubyte liFileSystem::DetermineFlag(liString filename)
{
	if (filename.Contains(".bmp")) {
		return LIFILE_BINARY;
	} else if (filename.Contains(".bin")) {
		return LIFILE_BINARY;
	} else if (filename.Contains(".wav")) {
		return LIFILE_BINARY;
	} else if (filename.Contains(".ttf")) {
		return LIFILE_BINARY;
	}
	return LIFILE_TEXT;
}

liList<liFile*> liFileSystem::GetFiles()
{
	return files;
}

liList<liFileSystem*> liFileSystem::GetFolders()
{
	return folders;
}

void liFileSystem::PrintFS()
{
	for (int i = 0; i < folders.Size(); i++) {
		printf("%s\n", folders[i]->head.c_str());
		folders[i]->PrintFS();
	}

	for (int i = 0; i < files.Size(); i++) {
		printf("%s\n", files[i]->complete_path.c_str());
	}
}
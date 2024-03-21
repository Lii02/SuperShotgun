#include "ConfigFile.h"

ConfigFile::ConfigFile()
{
}

ConfigFile::~ConfigFile()
{
}

liString ConfigFile::GetValue(liString key)
{
	return values.Find(key);
}

liFile* ConfigFile::WriteFile(liString name, liFileSystem* fs) {
	liFile* file = fs->AddFile(name + ".txt");
	file->BeginWrite();
	for (int i = 0; i < values.Size(); i++) {
		auto pair = values.At(i);
		file->WriteString(pair.first.c_str());
		file->WriteString(" = ");
		file->WriteString(pair.second.c_str());
		file->WriteChar('\n');
	}
	file->Close();
	return file;
}

void ConfigFile::AddValue(liString key, int value)
{
	values.Push(key, liString::IntToString(value));
}

void ConfigFile::AddValue(liString key, bool value)
{
	values.Push(key, liString::IntToString(value));
}

void ConfigFile::AddValue(liString key, float value)
{
	values.Push(key, liString::FloatToString(value));
}

ConfigFile* ConfigFile::Parse(liFile* file)
{
	ConfigFile* cfile = new ConfigFile();
	liString file_data = file->Read();
	auto lines = file_data.Tokenize('\n');
	for (auto it = lines.Begin(); it != lines.End(); it++) {
		auto line = *it;
		line->Trim();
		auto parts = line->Tokenize('=');
		liPair<liString, liString> val;
		val.first = liString(*parts[0]);
		val.second = liString(*parts[1]);
		parts.DeleteDataPointers();
		cfile->values.Push(val.first, val.second);
	}
	lines.DeleteDataPointers();
	return cfile;
}
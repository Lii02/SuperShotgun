#include "File.h"

liFile::liFile(liString complete_path, liString short_path, ubyte flag)
{
	this->complete_path = complete_path;
	this->short_path = short_path;
	this->flag = flag;
}

liFile::~liFile()
{
	if (flag & LIFILE_OPEN)
		Close();
}

liString liFile::Read()
{
	char mode[3];
	memset(&mode, 0, 3);
	mode[0] = 'r';
	
	if (flag & LIFILE_BINARY) {
		mode[1] = 'b';
	}
	handle = fopen(complete_path.c_str(), mode);
	flag |= (handle ? LIFILE_OPEN : 0);
	liString data;
	if (handle) {
		fseek(handle, 0, SEEK_END);
		size_t size = ftell(handle);
		rewind(handle);
		if (flag & LIFILE_READ) {
			if (flag & LIFILE_BINARY) {
				unsigned char* temp_str = new unsigned char[size];
				memset(temp_str, 0, size);
				fread(temp_str, size, 1, handle);
				data = liString(temp_str, size);
				delete[] temp_str;
			}
			else {
				char* temp_str = new char[size + 1];
				memset(temp_str, 0, size);
				fread(temp_str, size, 1, handle);
				data = liString(temp_str);
				delete[] temp_str;
			}
		}
		fclose(handle);
	}
	return data;
}

void liFile::BeginWrite()
{
	char mode[3];
	memset(&mode, 0, 3);
	mode[0] = 'w';

	if (flag & LIFILE_BINARY) {
		mode[1] = 'b';
	}
	handle = fopen(complete_path.c_str(), mode);
	flag |= (handle ? LIFILE_OPEN : 0);
}

void liFile::Close()
{
	RemoveFlag(LIFILE_OPEN);
	if (handle)
		fclose(handle);
}

void liFile::WriteChar(char c)
{
	fwrite((void*)&c, 1, 1, handle);
}

void liFile::WriteUByte(ubyte c)
{
	fwrite((void*)&c, 1, 1, handle);
}

void liFile::WriteString(cstring str)
{
	fwrite((void*)str, strlen(str), 1, handle);
}

liString liFile::GetCompletePath() const
{
	return complete_path;
}

liString liFile::GetShortPath() const
{
	return short_path;
}

ubyte liFile::GetFlag() const
{
	return flag;
}

void liFile::AddFlag(ubyte flag)
{
	this->flag |= flag;
}

void liFile::RemoveFlag(ubyte flag)
{
	this->flag &= ~flag;
}
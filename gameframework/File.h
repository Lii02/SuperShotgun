#ifndef FRAMEWORK_FILE_H
#define FRAMEWORK_FILE_H
#include <lilib/EngineDefs.h>
#include <lilib/LiString.h>

#define LIFILE_READ 0b10000000
#define LIFILE_WRITE 0b01000000
#define LIFILE_TEXT 0b00100000
#define LIFILE_BINARY 0b00010000
#define LIFILE_OPEN 0b00001000

class liFileSystem;

class liFile {
	friend class liFileSystem;
private:
	liString short_path, complete_path;
	ubyte flag;
	FILE* handle;
public:
	liFile() {}
	liFile(liString complete_path, liString short_path, ubyte flag);
	~liFile();

	liString Read();
	void BeginWrite();
	void Close();

	void WriteChar(char c);
	void WriteUByte(ubyte c);
	void WriteString(cstring str);

	liString GetCompletePath() const;
	liString GetShortPath() const;
	ubyte GetFlag() const;
	void AddFlag(ubyte flag);
	void RemoveFlag(ubyte flag);
};

#endif
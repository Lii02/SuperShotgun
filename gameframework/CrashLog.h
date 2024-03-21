#ifndef GAMEFRAMEWORK_CRASHLOG_H
#define GAMEFRAMEWORK_CRASHLOG_H
#include <lilib/EngineDefs.h>
#include "FileSystem.h"

class CrashLog {
public:
	static liFileSystem* logs_folder;
	static void SetupCrashLogs(liFileSystem* folder);

	static void WriteLog(liString message);
};

#endif
#include "CrashLog.h"
#include <lilib/Misc.h>

liFileSystem* CrashLog::logs_folder = nullptr;

void CrashLog::SetupCrashLogs(liFileSystem* folder)
{
	logs_folder = folder;
}

void CrashLog::WriteLog(liString message)
{
	liString path = "log";
	path.Append(LiLib_GetTimeString());
	path.Append(".txt");
	auto file = logs_folder->AddFile(path);
	file->BeginWrite();
	file->WriteString("Crash Log: ");
	file->WriteString(message.c_str());
	file->Close();
}
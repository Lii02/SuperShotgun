#ifndef FRAMEWORK_DEBUG_H
#define FRAMEWORK_DEBUG_H
#include <lilib/EngineDefs.h>
#include <lilib/LiString.h>

class Debug {
public:
	static void Log(liString message);
	static void LogWarning(liString message);
	static void LogError(liString message);
};

#endif
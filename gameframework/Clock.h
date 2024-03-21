#ifndef CLOCK_H
#define CLOCK_H
#include <lilib/EngineDefs.h>

class liClock {
private:
	float delta_time;
	double last_frame;
public:
	void Start();
	float DeltaTime();
};

#endif
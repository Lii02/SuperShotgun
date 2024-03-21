#ifndef GAMEFRAMEWORK_HDR_H
#define GAMEFRAMEWORK_HDR_H
#include <lilib/EngineDefs.h>
#include "IEffect.h"

class HDREffect : public IEffect {
private:
	float exposure;
public:
	HDREffect(float exposure, liContentManager* content, liVector2i screen);
	~HDREffect();

	virtual void Update() override;
};

#endif
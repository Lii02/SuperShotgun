#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <lilib/EngineDefs.h>
#include <lilib/math/Matrices.h>

class liTransform {
private:
public:
	liVector3f position, rotation, scale;

	liTransform();
	liTransform(liVector3f position, liVector3f rotation, liVector3f scale);
	liMatrix4x4 ToTransformMatrix();
	liMatrix4x4 ToRelativeMatrix(liTransform parent);
	liMatrix4x4 ToViewMatrix();
};

#endif
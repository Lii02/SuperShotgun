#include "Transform.h"
#include <lilib/math/MathHelper.h>

liTransform::liTransform()
{
	this->scale = liVector3f(1, 1, 1);
}

liTransform::liTransform(liVector3f position, liVector3f rotation, liVector3f scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

liMatrix4x4 liTransform::ToTransformMatrix()
{
	return liMatrix4x4::TranslationMatrix(position) *
		liMatrix4x4::RotationMatrix(liMathHelper::ToRadians(rotation.x), liVector3f(1, 0, 0)) *
		liMatrix4x4::RotationMatrix(liMathHelper::ToRadians(rotation.y), liVector3f(0, 1, 0)) *
		liMatrix4x4::RotationMatrix(liMathHelper::ToRadians(rotation.z), liVector3f(0, 0, 1)) * liMatrix4x4::ScaleMatrix(scale);
}

liMatrix4x4 liTransform::ToRelativeMatrix(liTransform parent)
{
	return liMatrix4x4::TranslationMatrix(parent.position + position) *
		liMatrix4x4::RotationMatrix(liMathHelper::ToRadians(parent.rotation.x + rotation.x), liVector3f(1, 0, 0)) *
		liMatrix4x4::RotationMatrix(liMathHelper::ToRadians(parent.rotation.y + rotation.y), liVector3f(0, 1, 0)) *
		liMatrix4x4::RotationMatrix(liMathHelper::ToRadians(parent.rotation.z + rotation.z), liVector3f(0, 0, 1)) * liMatrix4x4::ScaleMatrix(parent.scale * scale);
}

liMatrix4x4 liTransform::ToViewMatrix()
{
	return liMatrix4x4::RotationMatrix(liMathHelper::ToRadians(rotation.x), liVector3f(1, 0, 0)) *
		liMatrix4x4::RotationMatrix(liMathHelper::ToRadians(rotation.y), liVector3f(0, 1, 0)) *
		liMatrix4x4::RotationMatrix(liMathHelper::ToRadians(rotation.z), liVector3f(0, 0, 1))
		* liMatrix4x4::ScaleMatrix(scale) * liMatrix4x4::TranslationMatrix(-position);
}
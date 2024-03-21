#ifndef LILIB_MATRICES_H
#define LILIB_MATRICES_H
#include <lilib/math/MathTypes.h>

class liMatrix4x4 {
private:
	liVector4f vecs[4];
public:
	liMatrix4x4();
	liMatrix4x4(liVector4f vectors[4]);
	liMatrix4x4(float values[4][4]);
	liMatrix4x4(float values[16]);

	void SetIdentity();
	void SetZero();
	liVector4f& operator[](int index);
	const liVector4f& operator[](int index) const;
	float* ToPtr();
	liMatrix4x4 Multiply(const liMatrix4x4& right);
	liMatrix4x4 operator*(const liMatrix4x4& right);
	void Translate(liVector3f vec);
	void Scale(liVector3f vec);
	void Rotate(float angle, liVector3f axis);

	static liMatrix4x4 TranslationMatrix(liVector3f vec);
	static liMatrix4x4 ScaleMatrix(liVector3f vec);
	static liMatrix4x4 RotationMatrix(float angle, liVector3f axis);
	static liMatrix4x4 Orthographic(float left, float right, float bottom, float top, float near_plane, float far_plane);
	static liMatrix4x4 Perspective(float fov, float aspect_ratio, float near_plane, float far_plane);
};

#endif
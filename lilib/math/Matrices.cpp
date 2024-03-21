#include "Matrices.h"
#include "MathHelper.h"

liMatrix4x4::liMatrix4x4()
{
	SetIdentity();
}

liMatrix4x4::liMatrix4x4(liVector4f vectors[4])
{
	memcpy(&vecs, vectors, 64);
}

liMatrix4x4::liMatrix4x4(float values[4][4])
{
	memcpy(&vecs, values, 64);
}

liMatrix4x4::liMatrix4x4(float values[16])
{
	memcpy(&vecs, values, 64);
}

void liMatrix4x4::SetIdentity()
{
	vecs[0].Set(1, 0, 0, 0);
	vecs[1].Set(0, 1, 0, 0);
	vecs[2].Set(0, 0, 1, 0);
	vecs[3].Set(0, 0, 0, 1);
}

void liMatrix4x4::SetZero()
{
	// A 4x4 float matrix is 64 bytes
	memset(&vecs, 0, 64);
}

liVector4f& liMatrix4x4::operator[](int index)
{
	return vecs[index];
}

const liVector4f& liMatrix4x4::operator[](int index) const
{
	return vecs[index];
}

float* liMatrix4x4::ToPtr()
{
	return vecs[0].ToPtr();
}

liMatrix4x4 liMatrix4x4::Multiply(const liMatrix4x4& right)
{
	float values[4][4];
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			float sum = 0.0f;
			for (int e = 0; e < 4; e++) {
				sum += vecs[e][row] * right[col][e];
			}
			values[col][row] = sum;
		}
	}
	return liMatrix4x4(values);
}

liMatrix4x4 liMatrix4x4::operator*(const liMatrix4x4& right)
{
	return Multiply(right);
}

void liMatrix4x4::Translate(liVector3f vec)
{
	vecs[3][0] = vec.x;
	vecs[3][1] = vec.y;
	vecs[3][2] = vec.z;
	vecs[3][3] = 1.0f;
}

void liMatrix4x4::Scale(liVector3f vec)
{
	vecs[0][0] = vec.x;
	vecs[1][1] = vec.y;
	vecs[2][2] = vec.z;
	vecs[3][3] = 1.0f;
}

void liMatrix4x4::Rotate(float angle, liVector3f axis)
{
	float c = cos(angle);
	float s = sin(angle);
	float omc = 1.0f - c;

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	vecs[0][0] = x * x * omc + c;
	vecs[0][1] = y * x * omc + z * s;
	vecs[0][2] = x * z * omc - y * s;
	vecs[1][0] = x * y * omc - z * s;
	vecs[1][1] = y * y * omc + c;
	vecs[1][2] = y * z * omc + x * s;
	vecs[2][0] = x * z * omc + y * s;
	vecs[2][1] = y * z * omc - x * s;
	vecs[2][2] = z * z * omc + c;
}

liMatrix4x4 liMatrix4x4::TranslationMatrix(liVector3f vec)
{
	liMatrix4x4 mat;
	mat.Translate(vec);
	return mat;
}

liMatrix4x4 liMatrix4x4::ScaleMatrix(liVector3f vec)
{
	liMatrix4x4 mat;
	mat.Scale(vec);
	return mat;
}

liMatrix4x4 liMatrix4x4::RotationMatrix(float angle, liVector3f axis)
{
	liMatrix4x4 mat;
	mat.Rotate(angle, axis);
	return mat;
}

liMatrix4x4 liMatrix4x4::Orthographic(float left, float right, float bottom, float top, float near_plane, float far_plane)
{
	liMatrix4x4 result;
	result[0][0] = 2.0f / (right - left);
	result[1][1] = 2.0f / (top - bottom);
	result[2][2] = -2.0f / (far_plane - near_plane);
	result[3][0] = -(left + right) / (right - left);
	result[3][1] = -(bottom + top) / (top - bottom);
	result[3][2] = -(far_plane + near_plane) / (far_plane - near_plane);
	result[3][3] = 1.0f;
	return result;
}

liMatrix4x4 liMatrix4x4::Perspective(float fov, float aspect_ratio, float near_plane, float far_plane)
{
	liMatrix4x4 result;
	float q = 1.0f / tan(liMathHelper::ToRadians(0.5f * fov));
	float a = q / aspect_ratio;
	float frustum_length = (near_plane - far_plane);
	float b = (near_plane + far_plane) / frustum_length;
	float c = (2.0f * near_plane * far_plane) / frustum_length;
	result[0][0] = a;
	result[1][1] = q;
	result[2][2] = b;
	result[2][3] = -1.0f;
	result[3][2] = c;
	result[3][3] = 1;
	return result;
}
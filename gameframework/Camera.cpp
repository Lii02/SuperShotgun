#include "Camera.h"

liCamera::liCamera(liCameraType type, float fov, float aspect_ratio, float far_plane, float near_plane)
	: liActor(liActorType::TYPE_CAMERA, liActorFlag::FLAG_CAMERA)
{
	this->type = type;
	this->fov = fov;
	this->aspect_ratio = aspect_ratio;
	this->far_plane = far_plane;
	this->near_plane = near_plane;
	SetTag("Camera");
	this->is_main = false;
}

liCamera::liCamera(liCameraType type, int width, int height, float far_plane, float near_plane)
	: liActor(liActorType::TYPE_CAMERA, liActorFlag::FLAG_CAMERA)
{
	this->type = type;
	this->width = width;
	this->height = height;
	this->far_plane = far_plane;
	this->near_plane = near_plane;
	SetTag("Camera");
	this->is_main = false;
}

void liCamera::Spawn()
{
	liActor::Spawn();
}

void liCamera::Shutdown()
{
	liActor::Shutdown();
}

void liCamera::Render(RenderShader* shader)
{
	liActor::Render(shader);
}

void liCamera::Update()
{
	liActor::Update();
	switch (type) {
	case liCameraType::TYPE_ORTHOGRAPHIC: {
		float left = 0;
		float right = width;
		float top = 0;
		float bottom = height;
		projection_matrix = liMatrix4x4::Orthographic(left, right, bottom, top, near_plane, far_plane);
	} break;
	case liCameraType::TYPE_PROJECTION: {
		projection_matrix = liMatrix4x4::Perspective(fov, aspect_ratio, near_plane, far_plane);
	} break;
	}
	view_matrix = transform.ToViewMatrix();
}

bool liCamera::IsMainCamera() const
{
	return is_main;
}

void liCamera::SetIsMainCamera(bool is_main)
{
	this->is_main = is_main;
}

liMatrix4x4 liCamera::GetProjectionMatrix() const
{
	return projection_matrix;
}

liMatrix4x4 liCamera::GetViewMatrix() const
{
	return view_matrix;
}

void liCamera::SetCameraType(liCameraType type)
{
	this->type = type;
}

liCameraType liCamera::GetCameraType() const
{
	return type;
}

void liCamera::SetDimensions(int width, int height)
{
	this->width = width;
	this->height = height;
}

void liCamera::SetAspectRatio(float aspect_ratio)
{
	this->aspect_ratio = aspect_ratio;
}

void liCamera::SetPlanes(float far_plane, float near_plane)
{
	this->far_plane = far_plane;
	this->near_plane = near_plane;
}

float liCamera::GetFOV() const
{
	return fov;
}

float liCamera::GetFar() const
{
	return far_plane;
}

float liCamera::GetNear() const
{
	return near_plane;
}
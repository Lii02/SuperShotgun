#ifndef CAMERA_H
#define CAMERA_H
#include "Actor.h"
#include "Transform.h"

enum liCameraType : ubyte {
	TYPE_PROJECTION,
	TYPE_ORTHOGRAPHIC
};

class liCamera : public liActor {
private:
	liMatrix4x4 view_matrix, projection_matrix;
	liCameraType type;
	bool is_main;
	float aspect_ratio, far_plane, near_plane, fov;
	int width, height;
public:
	liCamera(liCameraType type, float fov, float aspect_ratio, float far_plane, float near_plane);
	liCamera(liCameraType type, int width, int height, float far_plane, float near_plane);

	virtual void Spawn() override;
	virtual void Shutdown() override;
	virtual void Render(RenderShader* shader)override;
	virtual void Update() override;
	
	bool IsMainCamera() const;
	void SetIsMainCamera(bool is_main);
	liMatrix4x4 GetProjectionMatrix() const;
	liMatrix4x4 GetViewMatrix() const;
	void SetCameraType(liCameraType type);
	liCameraType GetCameraType() const;
	void SetDimensions(int width, int height);
	void SetAspectRatio(float aspect_ratio);
	void SetPlanes(float far_plane, float near_plane);
	float GetFOV() const;
	float GetFar() const;
	float GetNear() const;
};

#endif
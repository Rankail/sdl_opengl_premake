#ifndef SDL_GL_TEST_CAMERA_H
#define SDL_GL_TEST_CAMERA_H

#include "math/math.h"

enum class CameraDirection {
	LEFT,RIGHT,FORWARD,BACKWARD,UP,DOWN
};

class Camera {
public:
	Camera(Vec3f pos = Vec3f(), Vec3f up = Vec3f(0.f, 1.f, 0.f), float yaw = -90.f, float pitch = 0.f);

	Mat4f getViewMatrix() const;

	void processMove(CameraDirection dir, float dt);
	void processMouse(float xrel, float yrel, bool constrainPitch = true);

	Vec3f getPos() const { return pos; }

protected:
	void updateCameraVectors();

protected:
	Vec3f pos;
	Vec3f front;
	Vec3f up;
	Vec3f right;
	Vec3f worldUp;
	float yaw;
	float pitch;

	float moveSpeed;
	float mouseSense;
};

#endif
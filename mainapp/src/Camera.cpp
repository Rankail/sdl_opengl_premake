#include "Camera.h"

#include <algorithm>

Camera::Camera(Vec3f pos, Vec3f up, float yaw, float pitch)
    : front(0.f, 0.f, -1.f), moveSpeed(2.5f), mouseSense(.1f), pos(pos), worldUp(up), yaw(yaw), pitch(pitch) {
    updateCameraVectors();
}

Mat4f Camera::getViewMatrix() const {
    return Mat4f::lookAt(pos, pos+front, up);
}

void Camera::processMove(CameraDirection dir, float dt) {
    float vel = moveSpeed * dt;
    auto fVel = front * vel;
    auto rVel = right * vel;
    auto uVel = worldUp * vel;
    fVel.set(1, 0.f);
    rVel.set(1, 0.f);

    if (dir == CameraDirection::FORWARD) pos += fVel;
    else if (dir == CameraDirection::BACKWARD) pos -= fVel;
    else if (dir == CameraDirection::LEFT) pos -= rVel;
    else if (dir == CameraDirection::RIGHT) pos += rVel;
    else if (dir == CameraDirection::UP) pos += uVel;
    else if (dir == CameraDirection::DOWN) pos -= uVel;
}

void Camera::processMouse(float xrel, float yrel, bool constrainPitch) {
    xrel *= mouseSense;
    yrel *= mouseSense;

    yaw += xrel;
    pitch -= yrel;

    if (constrainPitch) {
        pitch = std::clamp(pitch, -89.f, 89.f);
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    Vec3f front;
    float pitch = degToRad(this->pitch);
    float yaw = degToRad(this->yaw);
    front.set(0, cos(yaw) * cos(pitch));
    front.set(1, sin(pitch));
    front.set(2, sin(yaw) * cos(pitch));
    this->front = front.normalized();
    right = front.cross(worldUp).normalized();
    up = right.cross(front).normalized();
}

#include "raylib.h"
#include "raymath.h"
#include "camera.h"

FPSCamera::FPSCamera(Vector3 pos, float sens, float fovy)
    : position(pos),
      sensitivity(sens),
      yaw(0.0f),
      pitch(0.0f),
      front({0.0f, 0.0f, -1.0f}),
      up({0.0f, 1.0f, 0.0f}),
      camera(Camera3D{
          .position = pos,
          .target = Vector3Add(pos, {0.0f, 0.0f, -1.0f}),
          .up = {0.0f, 1.0f, 0.0f},
          .fovy = fovy,
          .projection = CAMERA_PERSPECTIVE
      }) {}

FPSCamera::~FPSCamera() {}

void FPSCamera::update() {
    Vector2 mouseDelta = GetMouseDelta();
    yaw -= mouseDelta.x * sensitivity;
    pitch -= mouseDelta.y * sensitivity;

    //TraceLog(LOG_INFO, "Yaw: %f, Pitch: %f", yaw, pitch);
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    front.x = cosf(pitch * DEG2RAD) * sinf(yaw * DEG2RAD);
    front.y = sinf(pitch * DEG2RAD);
    front.z = cosf(pitch * DEG2RAD) * cosf(yaw * DEG2RAD);
    front = Vector3Normalize(front);

    camera.target = Vector3Add(position, front);
    camera.up = up;
}

Camera3D FPSCamera::getCamera() {
    return camera;
}

void FPSCamera::setPosition(Vector3 pos) {
    position = pos;
    camera.position = pos;
    camera.target = Vector3Add(position, front);
}

Vector3 FPSCamera::getDirection() {
    return front;
}

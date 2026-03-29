#pragma once
#include "raylib.h"

class FPSCamera
{
private:
    float yaw, pitch; // yaw - поворот по горизонтали, pitch - поворот по вертикали
    float sensitivity; // сенса
    Vector3 position; // где камера находится
    Vector3 front; // куда смотрим
    Vector3 up; // нормаль к плоскости, на которой смотрим
    Camera3D camera; // сама камера
public:
    FPSCamera(Vector3 pos, float sens = 0.1f, float fovy = 60.0f);
    ~FPSCamera();

    void update();
    Camera3D getCamera();
    Vector3 getDirection();
    void setPosition(Vector3 pos);
    Vector3 getPosition();
    Vector3 getUp();
};
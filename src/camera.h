#include "raylib.h"

class FPSCamera
{
private:
    float yaw, pitch; // yaw - поворот по горизонтали, pitch - поворот по вертикали
    float sensitivity; // сенса
    Vector3 position; // где камера находится
    Vector3 front, normal; // куда смотрим и нормаль к плоскости, на которой смотрим
public:
    FPSCamera(/* args */);
    ~FPSCamera();
};

FPSCamera::FPSCamera(/* args */)
{
}

FPSCamera::~FPSCamera()
{
}

#pragma once
#include "raylib.h"
#include "camera.h"

class Player
{
    private:
        FPSCamera camera;
        Vector3 position;
        float velocityY;
    public:
        Player(Vector3 pos);
        ~Player();
        void update();
        Camera3D getCamera();
        Vector3 getPosition();
        bool isGrounded();
        float getVelocityY();
};

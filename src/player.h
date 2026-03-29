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
        float getRunMultiplier() const;
        void handleHorizontalMovement(float deltaTime, float runMultiplier);
        Vector3 getHorizontalDirection();
        Vector3 getRightDirection();
        void moveAlongVector(Vector3 direction, float distance);
        void handleJump();
        void applyPhysics(float deltaTime);
};

#include "raylib.h"
#include "camera.h"
#include "player.h"
#include "raymath.h"
#include "format"

constexpr float groundLevel = 1.0f;
constexpr float speed = 10.0f;
constexpr float gravity = -10.0f;

Player::Player(Vector3 pos) : camera(pos), position(pos), velocityY(0.0f) {}

Player::~Player() {}

void Player::update() {
    float deltaTime = GetFrameTime();
    // process multiplier for running
    float runMultiplier = 1.0f;
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        runMultiplier = 2.0f;
    }

    // process movement, only x and z axes
    if (IsKeyDown(KEY_W)) {
        Vector3 dir = camera.getDirection();
        dir.y = 0.0f;
        // can run only forward
        Vector3 movementVector = Vector3Scale(Vector3Normalize(dir), speed*runMultiplier*deltaTime);
        // we shouldn't move in y direction
        movementVector.y = 0.0f;

        position = Vector3Add(position, movementVector);
    }
    if (IsKeyDown(KEY_S)) {
        Vector3 dir = camera.getDirection();
        dir.y = 0.0f;
        Vector3 movementVector = Vector3Scale(Vector3Normalize(dir), speed*runMultiplier*deltaTime);
        // we shouldn't move in y direction
        movementVector.y = 0.0f;

        position = Vector3Subtract(position, movementVector);
    }
    if (IsKeyDown(KEY_A)) {
        position = Vector3Subtract(position,
             Vector3Scale(
                Vector3Normalize(
                    Vector3CrossProduct(
                        camera.getDirection(),
                        camera.getUp()
                    )
                ), 
               speed*deltaTime));
    }
    if (IsKeyDown(KEY_D)) {
        position = Vector3Add(position, 
            Vector3Scale(
                Vector3Normalize(
                    Vector3CrossProduct(
                        camera.getDirection(),
                        camera.getUp()
                    )
                ),
                speed*deltaTime)
            );
    }

    // process jumping
    if (IsKeyDown(KEY_SPACE) && isGrounded()) {
        velocityY = 5.0f;
    }
    
    //TraceLog(LOG_INFO, std::format("Velocity Y: %f", velocityY).c_str());
    velocityY += gravity * deltaTime;
    position.y += velocityY * deltaTime;
    if (isGrounded()){
        velocityY = 0.0f;
        position.y = groundLevel;
    }
    
    //process camera
    camera.setPosition(position);
    camera.update();
}

Camera3D Player::getCamera() {
    return camera.getCamera();
}

Vector3 Player::getPosition() {
    return position;
}

bool Player::isGrounded() {
    return position.y <= groundLevel;
}

float Player::getVelocityY() {
    return velocityY;
}

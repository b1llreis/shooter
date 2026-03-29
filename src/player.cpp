#include "raylib.h"
#include "camera.h"
#include "player.h"
#include "raymath.h"
#include "format"

constexpr float groundLevel = 1.0f;
constexpr float speed = 10.0f;
constexpr float gravity = -10.0f;
constexpr float jumpHeight = 5.0f;

Player::Player(Vector3 pos) : camera(pos), position(pos), velocityY(0.0f) {}

Player::~Player() {}

void Player::update() {
    float deltaTime = GetFrameTime();
    float runMultiplier = getRunMultiplier();
    
    handleHorizontalMovement(deltaTime, runMultiplier);
    handleJump();
    applyPhysics(deltaTime);
    
    camera.setPosition(position);
    camera.update();
}

float Player::getRunMultiplier() const{
    return IsKeyDown(KEY_LEFT_SHIFT) ? 2.0f : 1.0f;
}

void Player::handleHorizontalMovement(float deltaTime, float runMultiplier) {
    Vector3 forward = getHorizontalDirection();
    
    if (IsKeyDown(KEY_W)) {
        moveAlongVector(forward, speed * runMultiplier * deltaTime);
    }
    if (IsKeyDown(KEY_S)) {
        moveAlongVector(forward, -speed * runMultiplier * deltaTime);
    }
    if (IsKeyDown(KEY_A)) {
        Vector3 right = getRightDirection();
        moveAlongVector(right, -speed * deltaTime);
    }
    if (IsKeyDown(KEY_D)) {
        Vector3 right = getRightDirection();
        moveAlongVector(right, speed * deltaTime);
    }
}

Vector3 Player::getHorizontalDirection() {
    return Vector3Normalize(Vector3{ camera.getDirection().x, 0.0f, camera.getDirection().z });
}

Vector3 Player::getRightDirection() {
    return Vector3Normalize(Vector3CrossProduct(camera.getDirection(), camera.getUp()));
}

void Player::moveAlongVector(Vector3 direction, float distance) {
    position = Vector3Add(position, Vector3Scale(direction, distance));
}

void Player::handleJump() {
    if (IsKeyPressed(KEY_SPACE) && isGrounded()) {
        velocityY = jumpHeight;
    }
}

void Player::applyPhysics(float deltaTime) {
    velocityY += gravity * deltaTime;
    position.y += velocityY * deltaTime;

    if (isGrounded()) {
        position.y = groundLevel;
        velocityY = 0.0f;
    }
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

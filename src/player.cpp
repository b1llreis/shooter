#include "raylib.h"
#include "camera.h"
#include "player.h"
#include "raymath.h"

Player::Player(Vector3 pos) : camera(pos), position(pos) {}

Player::~Player() {}

void Player::update() {
    if (IsKeyDown(KEY_W)) {
        position = Vector3Add(position, Vector3Scale(camera.getDirection(), 0.1f));
    }
    if (IsKeyDown(KEY_S)) {
        position = Vector3Subtract(position, Vector3Scale(camera.getDirection(), 0.1f));
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
             0.1f));
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
                0.1f)
            );
    }
    if (IsKeyDown(KEY_SPACE)) {
        position.y += 0.1f;
    }
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        position.y -= 0.1f;
    }
    camera.setPosition(position);
    camera.update();
}

Camera3D Player::getCamera() {
    return camera.getCamera();
}

Vector3 Player::getPosition() {
    return position;
}
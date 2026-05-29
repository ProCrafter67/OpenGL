#pragma once

#include "camera.h"

class FirstPersonController
{
public:

    FirstPersonController(glm::vec3 Position)
    {
        position = Position;
    }

    void update(float deltaTime)
    {
        if (position.y < 3) {
            position.y = 3;
            vert_velocity = 0;
        } else {
            vert_velocity += gravity * deltaTime;
            position.y -= vert_velocity * deltaTime;
        }
    }

private:
    glm::vec3 position;
    float vert_velocity;
    float gravity = -9.81f;
};
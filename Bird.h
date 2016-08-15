#pragma once

#include <xge/util/GameTime.h>
#include <glm/vec2.hpp>

class Bird {
public:
    float x, y;
    const float width = 45.f, height = 32.f;
    bool killed = false;
    float rotation = 0;

    bool canFly = true;

    glm::vec2 velocity;

    const float gravity = 18.f;
    const float flyVelocity = 510.f;

    virtual void draw(xge::GameTime const&);
    virtual void update(xge::GameTime const&);
    virtual void resetPosition();
    virtual void fly();
};
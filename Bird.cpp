#include <xge/render/MeshBuilder.h>
#include "Bird.h"
#include "MGame.h"
#include <cmath>

using namespace xge;

float dis(glm::vec2 a, glm::vec2 b) {
    return (float) sqrt((a.x - b.x)*(a.x - b.x)+(a.y - b.y)*(a.y - b.y));
}

glm::vec2 rotatePoint(glm::vec2 p1, glm::vec2& p2, float angle) {
    float s = (float) sin(angle);
    float c = (float) cos(angle);

    p2.x -= p1.x;
    p2.y -= p1.y;

    glm::vec2 pnew(p2.x * c - p2.y * s, p2.x * s + p2.y * c);

    p2 = p1 + pnew;
    return p2;
}

void Bird::draw(xge::GameTime const& time) {
    update(time);

    glm::vec2 sr(x + width/2.f, y + height/2.f);

    glm::vec2 lb(x, y), lt(x, y + height), rb(x + width, y), rt(x + width, y + height);

    rotatePoint(sr, lb, rotation);
    rotatePoint(sr, lt, rotation);
    rotatePoint(sr, rb, rotation);
    rotatePoint(sr, rt, rotation);

    MeshBuilder builder(MGame::instance->config);
    builder.setPrimaryTexture(MGame::instance->gameTexture);
    builder.push(lb, glm::vec2(0.58f, 0.7f));
    builder.push(rb, glm::vec2(0.62f, 0.7f));
    builder.push(lt, glm::vec2(0.58f, 0.75f));
    builder.push(rt, glm::vec2(0.62f, 0.75f));
    builder.push(lt, glm::vec2(0.58f, 0.75f));
    builder.push(rb, glm::vec2(0.62f, 0.7f));
//    builder.rect({x,y}, {x + width, y + height}, {0.58f, 0.7f}, {0.62f, 0.75f}, {});
    builder.build(true)->draw();
}

void Bird::update(xge::GameTime const& time) {
    if (MGame::instance->getKeyboard().isPressed('W')) {
        if (canFly)
            fly();
        canFly = false;
    }
    else
        canFly = true;
    velocity -= gravity;
    y += float(time.getDelta()) * velocity.y;
    rotation = velocity.y / flyVelocity;
    rotation *= 70.f;
    if (rotation < -90.f) rotation = -90.f;
    rotation *= (2.f*float(M_PI))/360.f;
}

void Bird::resetPosition() {
    x = (MGame::instance->getWidth() - width) / 2.f;
    y = (MGame::instance->getHeight() - height) / 2.f;
}

void Bird::fly() {
    velocity.y = flyVelocity;
}
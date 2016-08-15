#include <xge/render/MeshBuilder.h>
#include "Pipe.h"
#include "MGame.h"

using namespace xge;

Pipe::Pipe(float x, float y, float width, float height, float speed) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->speed = speed;
}

void Pipe::draw(xge::GameTime const & time) {
    update(time);
    MeshBuilder builder(MGame::instance->config);
    builder.setPrimaryTexture(MGame::instance->gameTexture);
    builder.rect({x, y}, {x+width, y+height}, {0.728f, 0.531f}, {0.79f, 1.f}, {});
    builder.build(true)->draw();
    builder.rect({x, y+height+150.f}, {x+width, 500.f}, {0.662f, 0.473f}, {0.727f, 1.f}, {});
    builder.build(true)->draw();
}


void Pipe::update(xge::GameTime const &) {
    x -= speed;


 //   if(x<0.f)
}
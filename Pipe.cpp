#include <xge/render/MeshBuilder.h>
#include "Pipe.h"
#include "MGame.h"

using namespace xge;

Pipe::Pipe(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Pipe::draw(xge::GameTime const & time) {
    update(time);
    MeshBuilder builder(MGame::instance->config);
    builder.setPrimaryTexture(MGame::instance->gameTexture);
    builder.rect({x, y}, {x+width, y+height}, {0.55f, 0.65f}, {0.99f, 0.9f}, {});
    builder.build(true)->draw();
}


void Pipe::update(xge::GameTime const &) {

}
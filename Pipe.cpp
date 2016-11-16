#include <xge/render/MeshBuilder.h>
#include "Pipe.h"
#include "MGame.h"
#include <cmath>
#include <algorithm>

using namespace xge;
Pipe::Pipe(float x, float y, float extent, float speed) {
    this->x = x;
    this->y = y;
    this->extent = extent;
    this->speed = speed;
}

void Pipe::draw(xge::GameTime const & time) {
    update(time);
    MeshBuilder builder(MGame::instance->config);
    builder.setPrimaryTexture(MGame::instance->gameTexture);
    builder.rect({x, y-extent-125.f}, {x+width, y+height-extent}, {0.728f, 0.531f}, {0.79f, 1.f}, {});
    builder.build(true)->draw();
    builder.rect({x, y+height-extent+150.f}, {x+width, y+height-extent+500.f}, {0.662f, 0.473f}, {0.727f, 1.f}, {});
    builder.build(true)->draw();
}


void Pipe::update(xge::GameTime const &) {
    if(MGame::bird->killed) return;
    x -= speed;
    //sprawdz kolizji
    float x1, y1, x2, y2, w1, w2, x_val[7], y_val[7];
    x_val[0] = x;
    y_val[0] = y-extent-125.f;
    x_val[1] = x;
    y_val[1] = y+height-extent;
    x_val[2] = x+width;
    y_val[2] = y+height-extent;
    x_val[3] = x;
    y_val[3] = y+height-extent+500.f;
    x_val[4] = x;
    y_val[4] = y+height-extent+150.f;
    x_val[5] = x+width;
    y_val[5] = y+height-extent+150.f;
    for(int i = 0; i <= 4; i++) {
        if(i==2) continue;
        x1 = x_val[i];
        y1 = y_val[i];
        x2 = x_val[i+1];
        y2 = y_val[i+1];
        float h1 = MGame::bird->x + MGame::bird->radius;
        float h2 = MGame::bird->x;// - MGame::bird->radius;
        float h3 = MGame::bird->y + MGame::bird->radius;
        float h4 = MGame::bird->y - MGame::bird->radius;
        bool c1 = (h1<= std::max(x1, x2)+MGame::bird->radius && std::min(x1, x2)-MGame::bird->radius <= h1); // c1 - condition one
        bool c2 = (h2<= std::max(x1, x2)+MGame::bird->radius && std::min(x1, x2)-MGame::bird->radius <= h2);
        bool c3 = (h3<= std::max(y1, y2)+MGame::bird->radius && std::min(y1, y2)-MGame::bird->radius <= h3);
        bool c4 = (h4<= std::max(y1, y2)+MGame::bird->radius && std::min(y1, y2)-MGame::bird->radius <= h4);
        if((c1 or c2) and (c3 or c4))
            MGame::bird->killed = true;
    }
}
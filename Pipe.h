#pragma once

#include <xge/util/GameTime.h>

class Pipe {
public:
    float x, y;
    float width = 55, height = 225;
    float speed, extent;
    Pipe(float x, float y, float extent, float speed);
    virtual void draw(xge::GameTime const&);
    virtual void update(xge::GameTime const&);
};

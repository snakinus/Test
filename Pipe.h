#pragma once

#include <xge/util/GameTime.h>

class Pipe {
public:
    float x, y;
    float width, height;
    Pipe(float x, float y, float width, float height);
    virtual void draw(xge::GameTime const&);
    virtual void update(xge::GameTime const&);
};

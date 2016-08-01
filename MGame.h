#pragma once
#include <xge/Game.h>
#include <xge/render/Shader.h>
#include <xge/render/MeshBuilderConfig.h>

class MGame : public xge::Game {
private:
    std::shared_ptr<xge::ShaderProgram> shader;
    xge::MeshBuilderConfig config;
public:
    int pos = 1;
    float col = 0.01;
    virtual void init();
    virtual void draw(xge::GameTime const &time);
};
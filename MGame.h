#pragma once
#include <xge/Game.h>
#include <xge/render/Shader.h>
#include <xge/render/MeshBuilderConfig.h>
#include "Bird.h"
#include "Pipe.h"
#include <vector>

class MGame : public xge::Game {
private:
    std::shared_ptr<xge::ShaderProgram> shader/*, shaderRepeat*/;
public:

    Bird* bird;
    Pipe* pipe;

    std::vector<Pipe> v;

    std::shared_ptr<xge::Texture> gameTexture;

    xge::MeshBuilderConfig config/*, configRepeat*/;
    void drawBackground();

    virtual void init();
    virtual void draw(xge::GameTime const &time);

    static MGame* instance;
};
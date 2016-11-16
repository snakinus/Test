#include "MGame.h"
#include <xge/opengl.h>
#include <xge/render/MeshBuilder.h>
#include <xge/render/Texture.h>
#include <xge/util/Image.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace xge;
using namespace std;

MGame* MGame::instance = nullptr;
Bird* MGame::bird = nullptr;

void MGame::init() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader = std::shared_ptr<ShaderProgram>(new ShaderProgram());
    shader->attach(Shader::createFromAssets(ShaderType::Vertex, "shaders/shader.vertex"));
    shader->attach(Shader::createFromAssets(ShaderType::Fragment, "shaders/shader.fragment"));
    shader->link();

    shaderRepeat = std::shared_ptr<ShaderProgram>(new ShaderProgram());
    shaderRepeat->attach(Shader::createFromAssets(ShaderType::Vertex, "shaders/shaderRepeat.vertex"));
    shaderRepeat->attach(Shader::createFromAssets(ShaderType::Fragment, "shaders/shaderRepeat.fragment"));
    shaderRepeat->link();

    config = MeshBuilderConfig(shader);
    config.setPrimaryTextureUniform("uSampler");
    config.addAttribute("aPosition", xge::ShaderValueType::Vec2, MeshAttributeUsage::POSITION);
    config.addAttribute("aTextureCoord", xge::ShaderValueType::Vec2, MeshAttributeUsage::TEXTURE_UV);

    configRepeat = MeshBuilderConfig(shaderRepeat);
    configRepeat.setPrimaryTextureUniform("uSampler");
    configRepeat.addAttribute("aPosition", xge::ShaderValueType::Vec2, MeshAttributeUsage::POSITION);
    configRepeat.addAttribute("aTextureCoord", xge::ShaderValueType::Vec2, MeshAttributeUsage::TEXTURE_UV);

    gameTexture = std::shared_ptr<Texture>(new Texture(Image::fromAsset("flappy bird textures.png")));

    pipe = new Pipe(1000, 0, 50, 2);
    v.push_back(*pipe);
    bird = new Bird();
    bird->resetPosition();
}

void MGame::drawBackground() {
    MeshBuilder builder(configRepeat);
    builder.setPrimaryTexture(gameTexture);
    builder.rect({0.f, 0.f}, {getWidth(), getHeight()}, {0.f, 0.f}, {0.3f, 1.f}, {});
    builder.build(true)->draw();
}

void MGame::draw(xge::GameTime const& time) {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 proj = glm::ortho(0.f, (float) getWidth(), 0.f, (float) getHeight(), 0.1f, 100.f);
    proj = glm::translate(proj, glm::vec3(0.f, 0.f, -1.f));

    shader->use();
    shader->getUniform("uProjectionMatrix", ShaderValueType::Matrix4).set((ShaderValue *) glm::value_ptr(proj));

    float val = 10.5f;
   shaderRepeat->use();
    shaderRepeat->getUniform("uProjectionMatrix", ShaderValueType::Matrix4).set((ShaderValue *) glm::value_ptr(proj));
  shaderRepeat->getUniform("bla", ShaderValueType::Float).set((ShaderValue *) &val);

    drawBackground();


    float farthest = 1000;
    for(int i = 0; i < v.size(); i++) {
        (&v[i])->draw(time);
        if(v[i].x<-200) {
            swap(v[i], v[v.size()-1]);
            v.pop_back();
        }
        while(v.size()<7) {
            float extent = (rand()%225);
            pipe = new Pipe(farthest+200, 0, extent, 2);
            v.push_back(*pipe);
            farthest += 200;
        }
    }
    bird->draw(time);

}
#include "MGame.h"
#include <xge/opengl.h>
#include <xge/render/MeshBuilder.h>
#include <xge/render/Texture.h>
#include <xge/util/Image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace xge;

MGame* MGame::instance = nullptr;

void MGame::init() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader = std::shared_ptr<ShaderProgram>(new ShaderProgram());
    shader->attach(Shader::createFromAssets(ShaderType::Vertex, "shaders/shader.vertex"));
    shader->attach(Shader::createFromAssets(ShaderType::Fragment, "shaders/shader.fragment"));
    shader->link();
/*
    shaderRepeat = std::shared_ptr<ShaderProgram>(new ShaderProgram());
    shaderRepeat->attach(Shader::createFromAssets(ShaderType::Vertex, "shaders/shader.vertex"));
    shaderRepeat->attach(Shader::createFromAssets(ShaderType::Fragment, "shaders/shader.fragment"));
    shaderRepeat->link();
*/
    config = MeshBuilderConfig(shader);
    config.setPrimaryTextureUniform("uSampler");
    config.addAttribute("aPosition", xge::ShaderValueType::Vec2, MeshAttributeUsage::POSITION);
    config.addAttribute("aTextureCoord", xge::ShaderValueType::Vec2, MeshAttributeUsage::TEXTURE_UV);
/*
    configRepeat = MeshBuilderConfig(shaderRepeat);
    configRepeat.setPrimaryTextureUniform("uSampler");
    configRepeat.addAttribute("aPosition", xge::ShaderValueType::Vec2, MeshAttributeUsage::POSITION);
    configRepeat.addAttribute("aTextureCoord", xge::ShaderValueType::Vec2, MeshAttributeUsage::TEXTURE_UV);
*/
    gameTexture = std::shared_ptr<Texture>(new Texture(Image::fromAsset("flappy bird textures.png")));

    pipe = new Pipe(0, 0, 350, 210);

    bird = new Bird();
    bird->resetPosition();
}

void MGame::drawBackground() {
    MeshBuilder builder(config);
    builder.setPrimaryTexture(gameTexture);
    builder.rect({0.f, 0.f}, {getWidth(), getHeight()}, {0.f, 0.f}, {0.30f, 1.f}, {});
    builder.build(true)->draw();
}

void MGame::draw(xge::GameTime const& time) {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 proj = glm::ortho(0.f, (float) getWidth(), 0.f, (float) getHeight(), 0.1f, 100.f);
    proj = glm::translate(proj, glm::vec3(0.f, 0.f, -1.f));

    shader->use();
    shader->getUniform("uProjectionMatrix", ShaderValueType::Matrix4).set((ShaderValue *) glm::value_ptr(proj));

//    shaderRepeat->use();
//    shaderRepeat->getUniform("uProjectionMatrix", ShaderValueType::Matrix4).set((ShaderValue *) glm::value_ptr(proj));

    drawBackground();

    pipe->draw(time);
    bird->draw(time);

}
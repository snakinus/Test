#include "MGame.h"
#include <xge/opengl.h>
#include <xge/render/MeshBuilder.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace xge;

void MGame::init() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader = std::shared_ptr<ShaderProgram>(new ShaderProgram());
    shader->attach(Shader::createFromAssets(ShaderType::Vertex, "shaders/shader.vertex"));
    shader->attach(Shader::createFromAssets(ShaderType::Fragment, "shaders/shader.fragment"));
    shader->link();

    config = MeshBuilderConfig(shader);
    config.addAttribute("aPosition", xge::ShaderValueType::Vec2, MeshAttributeUsage::POSITION);
    config.addAttribute("aColor", xge::ShaderValueType::Vec4, MeshAttributeUsage::COLOR);
}

void MGame::draw(xge::GameTime const& time) {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 proj = glm::ortho(0.f, (float) getWidth(), 0.f, (float) getHeight(), 0.1f, 100.f);
    proj = glm::translate(proj, glm::vec3(0.f, 0.f, -1.f));

    shader->getUniform("uProjectionMatrix", ShaderValueType::Matrix4).set((ShaderValue*) glm::value_ptr(proj));

    pos = 0;
    col = std::min(1.0f, col+0.01f);
    MeshBuilder builder(config);
    builder.push(glm::vec2(0.f+pos, 0.f), glm::vec4(col+0.f, 0.f, 0.f+col, 0.f));
    builder.push(glm::vec2(100.f+pos, 0.f), glm::vec4(1.f, col+0.f, 0.f, 1.f));
    builder.push(glm::vec2(0.f+pos, 100.f), glm::vec4(1.f, 0.f, col+0.f, 1.f));
    builder.build(true)->draw();
}
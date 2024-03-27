#include "Renderer.hpp"

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::draw(const VertexArray& vertexArray, const Shader& shader) const {
    vertexArray.bind();
    shader.bind();
    glDrawElements(GL_TRIANGLES, vertexArray.getElementCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

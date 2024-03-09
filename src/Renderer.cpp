#include "Renderer.hpp"

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const {
    vertexArray.bind();
    indexBuffer.bind();
    shader.bind();
    glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

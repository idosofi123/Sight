#pragma once
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

class Renderer {

private:

public:
    Renderer();
    ~Renderer();
    void draw(const VertexArray &vertexArray, const IndexBuffer &indexBuffer, const Shader &shdaer) const;
    void clear() const;
};
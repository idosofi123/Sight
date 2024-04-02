#pragma once
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include <memory>

class VertexArray {

private:
    unsigned int id;
    unsigned int elementCount;
    unsigned int vertexCount;

public:
    VertexArray(const VertexBuffer &buffer, const VertexBufferLayout &layout, const IndexBuffer &indexBuffer);
    VertexArray(VertexArray&&);
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&&) = delete;
    VertexArray();
    ~VertexArray();
    void bind() const;
    void bindBuffers(const VertexBuffer &buffer, const VertexBufferLayout &layout, const IndexBuffer &indexBuffer);
    void unbind() const;
    unsigned int getElementCount() const;
    unsigned int getVertexCount() const;
};
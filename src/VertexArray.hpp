#pragma once
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "NonCopyable.hpp"
#include <memory>

class VertexArray : public NonCopyable<VertexArray> {

private:
    unsigned int id;
    unsigned int elementCount;
    unsigned int vertexCount;

public:
    VertexArray(const VertexBuffer &buffer, const VertexBufferLayout &layout, const IndexBuffer &indexBuffer);
    VertexArray(VertexArray&&);
    VertexArray();
    ~VertexArray();
    void bind() const;
    void bindBuffers(const VertexBuffer &buffer, const VertexBufferLayout &layout, const IndexBuffer &indexBuffer);
    void unbind() const;
    unsigned int getElementCount() const;
    unsigned int getVertexCount() const;
};
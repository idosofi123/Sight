#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer() {}

VertexBuffer::~VertexBuffer() {}

GLenum VertexBuffer::getGLType() const {
    return GL_ARRAY_BUFFER;
}


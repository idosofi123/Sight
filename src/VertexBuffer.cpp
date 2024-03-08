#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer() : Buffer() {}

VertexBuffer::~VertexBuffer() {}

GLenum VertexBuffer::getGLType() const {
    return GL_ARRAY_BUFFER;
}


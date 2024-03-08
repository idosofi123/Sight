#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer() : Buffer() {}

IndexBuffer::~IndexBuffer() {}

GLenum IndexBuffer::getGLType() const {
    return GL_ELEMENT_ARRAY_BUFFER; 
}
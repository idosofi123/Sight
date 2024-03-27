#include "VertexArray.hpp"

VertexArray::VertexArray(const VertexBuffer &buffer, const VertexBufferLayout &layout, const IndexBuffer &indexBuffer) : VertexArray() {
    this->bindBuffers(buffer, layout, indexBuffer);
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &this->id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &this->id);
}

void VertexArray::bind() const {
    glBindVertexArray(this->id);
}

void VertexArray::bindBuffers(const VertexBuffer &buffer, const VertexBufferLayout &layout, const IndexBuffer &indexBuffer) {
    
    this->bind();
    buffer.bind();
    indexBuffer.bind();

    unsigned int currentOffset = 0, i = 0;

    for (const auto &attribute : layout.getAttributes()) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i++, attribute.count, attribute.type, attribute.normalized, layout.getStride(), (const void*)currentOffset);
        currentOffset += attribute.totalSize;
    }

    this->elementCount = indexBuffer.getCount();
    this->vertexCount = buffer.getCount();
    this->unbind();
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

unsigned int VertexArray::getElementCount() const { 
    return this->elementCount;
}

unsigned int VertexArray::getVertexCount() const {
    return this->vertexCount;
}

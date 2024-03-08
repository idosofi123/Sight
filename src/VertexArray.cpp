#include "VertexArray.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &this->id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &this->id);
}

void VertexArray::setBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout) {

    this->bind();
    buffer.bind();

    unsigned int currentOffset = 0, i = 0;

    for (const auto &attribute : layout.getAttributes()) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i++, attribute.count, attribute.type, attribute.normalized, layout.getStride(), (const void*)currentOffset);
        currentOffset += attribute.totalSize;
    }
    
}

void VertexArray::bind() const {
    glBindVertexArray(this->id);
}

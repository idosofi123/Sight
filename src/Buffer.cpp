#include "Buffer.hpp"

Buffer::Buffer() {
    glGenBuffers(1, &this->id);
}

Buffer::Buffer(Buffer &&buffer) : id(buffer.id), count(buffer.count) {
    buffer.id = 0;
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &this->id);
}

void Buffer::bind() const {
    glBindBuffer(this->getGLType(), this->id);
}

void Buffer::unbind() const {
    glBindBuffer(this->getGLType(), 0);
}

unsigned int Buffer::getId() const {
    return this->id;
}

unsigned int Buffer::getCount() const {
    return this->count;
}

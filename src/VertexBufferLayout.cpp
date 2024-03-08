#include "VertexBufferLayout.hpp"

VertexBufferLayout::VertexBufferLayout() {}

VertexBufferLayout::~VertexBufferLayout() {}

const std::vector<VertexAttribute>& VertexBufferLayout::getAttributes() const {
    return this->attributes;
}

unsigned int VertexBufferLayout::getStride() const {
    return this->stride;
}

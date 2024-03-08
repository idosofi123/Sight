#pragma once
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {

private:
    unsigned int id;

public:
    VertexArray();
    ~VertexArray();
    void setBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout);
    void bind() const;
};
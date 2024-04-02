#pragma once
#include "Buffer.hpp"

class VertexBuffer : public Buffer {

private:

protected:
    virtual GLenum getGLType() const override;

public:
    VertexBuffer();
    VertexBuffer(VertexBuffer &&buffer) : Buffer(std::move(buffer)) {}
    ~VertexBuffer();
    
};
#pragma once
#include "Buffer.hpp"
#include <type_traits>

class IndexBuffer : public Buffer {

private:

protected:
    virtual GLenum getGLType() const override;

public:
    IndexBuffer();
    IndexBuffer(IndexBuffer &&buffer) : Buffer(std::move(buffer)) {}
    ~IndexBuffer();

    template <typename T>
    void setData(std::vector<T> data) {
        static_assert(std::is_same<T, unsigned int>::value, "Index buffers can only store indices, represnted as unsigned ints.");
        Buffer::setData(data);
    }
};
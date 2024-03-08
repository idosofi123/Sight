#pragma once
#include "Buffer.hpp"
#include <type_traits>

class IndexBuffer : public Buffer {

private:

protected:
    virtual GLenum getGLType() const override;

public:
    IndexBuffer();
    ~IndexBuffer();

    template <typename T>
    void setData(const std::vector<T> &data) {
        static_assert(std::is_same<T, unsigned int>::value, "Index buffers can only store indices, represnted as unsigned ints.");
        Buffer::setData(data);
    }
};
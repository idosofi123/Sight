#pragma once
#include <GL/glew.h>
#include <vector>

class Buffer {

private:

protected:
    unsigned int id;
    virtual GLenum getGLType() const = 0;
    unsigned int count;

public:
    Buffer();
    Buffer(Buffer&&);
    Buffer(const Buffer&) = delete;
    Buffer& operator=(Buffer&&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    ~Buffer();
    void bind() const;
    void unbind() const;
    unsigned int getId() const;
    unsigned int getCount() const;

    template <typename T>
    void setData(std::vector<T> data) {
        this->bind();
        glBufferData(this->getGLType(), sizeof(T) * data.size(), data.data(), GL_STATIC_DRAW);
        this->count = data.size();
    }
};
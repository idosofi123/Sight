#pragma once
#include <GL/glew.h>
#include <vector>

class Buffer {

private:

protected:
    unsigned int id;
    virtual GLenum getGLType() const = 0;

public:
    Buffer();
    ~Buffer();
    void bind() const;
    void unbind() const;
    unsigned int getId() const;

    template <typename T>
    void setData(const std::vector<T> &data) {
        this->bind();
        glBufferData(this->getGLType(), sizeof(T) * data.size(), data.data(), GL_STATIC_DRAW);
    }
};
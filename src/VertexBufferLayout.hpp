#pragma once
#include <GL/glew.h>
#include <vector>

struct VertexAttribute {
    GLenum type;
    unsigned int count;
    unsigned int totalSize;
    bool normalized;
};

class VertexBufferLayout {

private:

    std::vector<VertexAttribute> attributes;
    unsigned int stride = 0;

    template <typename T>
    void addAttribute(GLenum type, unsigned int count, bool normalized) {
        this->attributes.push_back({ type, count, sizeof(T) * count, normalized });
        this->stride += (*this->attributes.rbegin()).totalSize;
    }

public:

    VertexBufferLayout();
    ~VertexBufferLayout();
    
    template <typename T>
    void addAttribute(unsigned int count, bool normalized) = delete;

    template <>
    void addAttribute<float>(unsigned int count, bool normalized) {
        this->addAttribute<float>(GL_FLOAT, count, normalized);
    }

    template <>
    void addAttribute<unsigned int>(unsigned int count, bool normalized) {
        this->addAttribute<unsigned int>(GL_UNSIGNED_INT, count, normalized);
    }

    template <>
    void addAttribute<int>(unsigned int count, bool normalized) {
        this->addAttribute<int>(GL_INT, count, normalized);
    }

    const std::vector<VertexAttribute>& getAttributes() const;
    unsigned int getStride() const;
};
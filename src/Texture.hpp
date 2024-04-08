#pragma once
#include <vector>
#include <GL/glew.h>
#include "NonCopyable.hpp"

class Texture : public NonCopyable<Texture> {

private:

protected:

    unsigned int id;
    int width;
    int height;
    int bytesPerPixel;
    virtual GLenum getGLType() const = 0;

public:
    
    Texture();
    Texture(Texture &&);
    virtual ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;
    int getWidth() const;
    int getHeight() const;
    unsigned int getId() const;
};
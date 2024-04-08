#include "Texture.hpp"
#include <GL/glew.h>

Texture::Texture() {
    glGenTextures(1, &this->id);
}

Texture::Texture(Texture &&texture) :
    id(texture.id),  
    width(texture.width),
    height(texture.height),  
    bytesPerPixel(texture.bytesPerPixel) {
        
    texture.id = 0;
}

Texture::~Texture() {
    glDeleteTextures(1, &this->id);
}

void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(this->getGLType(), this->id);
}

void Texture::unbind() const {
    glBindTexture(this->getGLType(), 0);
}

int Texture::getWidth() const {
    return this->width;
}

int Texture::getHeight() const {
    return this->height;
}

unsigned int Texture::getId() const {
    return this->id;
}

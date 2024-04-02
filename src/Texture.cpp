#include "Texture.hpp"
#include <GL/glew.h>
#include "vendor/stb_image.h"
#include <memory>
#include <iostream>

Texture::Texture(const std::string &filePath) {

    stbi_set_flip_vertically_on_load(true);
    std::unique_ptr<unsigned char> textureData{stbi_load(filePath.c_str(), &this->width, &this->height, &this->bytesPerPixel, 4)};

    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.get());
    glGenerateMipmap(GL_TEXTURE_2D);
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
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
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

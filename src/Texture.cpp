#include "Texture.hpp"
#include <GL/glew.h>
#include "vendor/stb_image.h"
#include <memory>

Texture::Texture(const std::string &filePath) {

    stbi_set_flip_vertically_on_load(true);
    std::unique_ptr<unsigned char> textureData{stbi_load(filePath.c_str(), &this->width, &this->height, &this->bytesPerPixel, 4)};

    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.get());
}

Texture::~Texture() {
    glBindTexture(GL_TEXTURE_2D, this->id);
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

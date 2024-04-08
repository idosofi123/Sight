#include "Texture2D.hpp"
#include "vendor/stb_image.h"
#include <memory>

GLenum Texture2D::getGLType() const {
    return GL_TEXTURE_2D;
}

Texture2D::Texture2D(const std::string &filePath) : Texture() {
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

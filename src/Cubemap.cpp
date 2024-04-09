#include "Cubemap.hpp"
#include "vendor/stb_image.h"
#include <memory>

Cubemap::Cubemap(const std::vector<std::string> &filePaths) : Texture() {

    stbi_set_flip_vertically_on_load(false);

    glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);

    for (size_t i = 0; i < filePaths.size(); i++) {
        std::unique_ptr<unsigned char> textureData{stbi_load(filePaths[i].c_str(), &this->width, &this->height, &this->bytesPerPixel, 4)};
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.get());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

Cubemap::~Cubemap() {}

GLenum Cubemap::getGLType() const {
    return GL_TEXTURE_CUBE_MAP;
}
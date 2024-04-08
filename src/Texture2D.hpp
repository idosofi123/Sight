#pragma once
#include "Texture.hpp"
#include <string>

class Texture2D : public Texture {

private:

protected:
    virtual GLenum getGLType() const override;

public:
    Texture2D(const std::string &filePath);

};
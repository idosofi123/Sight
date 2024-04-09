#pragma once
#include <string>
#include "Texture.hpp"

class Cubemap : public Texture {

private:

protected:

    virtual GLenum getGLType() const override;

public:
    Cubemap(const std::vector<std::string> &filePaths);
    ~Cubemap();

};
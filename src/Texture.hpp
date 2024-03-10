#pragma once
#include <vector>
#include <string>

class Texture {

private:
    unsigned int id;
    int width;
    int height;
    int bytesPerPixel;

public:
    Texture(const std::string &filePath);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;
    int getWidth() const;
    int getHeight() const;
};
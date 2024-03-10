#pragma once
#include <string>
#include <GL/glew.h>
#include <unordered_map>

class Shader {

private:
    unsigned int id;
    std::unordered_map<std::string, int> uniformLocations;
    int getUniformLocation(const std::string &name);

public:
    Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);
    ~Shader();
    void bind() const;
    void unbind() const;
    void setUnifrom4f(const std::string &name, float a, float b, float c, float d);
    void setUnifrom1i(const std::string &name, int value);
    
    static std::string readSourceFromFile(const std::string &filePath);
    static unsigned int compileShader(unsigned int type, const std::string &src);
};
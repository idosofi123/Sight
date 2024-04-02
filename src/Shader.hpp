#pragma once
#include <string>
#include <GL/glew.h>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>

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
    void setUniform4f(const std::string &name, float a, float b, float c, float d);
    void setUniform3f(const std::string &name, float a, float b, float c);
    void setUniform1f(const std::string &name, float a);
    void setUniform1i(const std::string &name, int value);
    void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);
    void setUniform1iArr(const std::string &name, const std::vector<int> arr);
    
    static std::string readSourceFromFile(const std::string &filePath);
    static unsigned int compileShader(unsigned int type, const std::string &src);
};
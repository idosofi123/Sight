#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

Shader::Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) {

    this->id = glCreateProgram();
    unsigned int vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(this->id, vertexShaderId);
    glAttachShader(this->id, fragmentShaderId);

    glLinkProgram(this->id);
    glValidateProgram(this->id);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

Shader::~Shader() {
    glDeleteProgram(this->id);
}

void Shader::bind() const {
    glUseProgram(this->id);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::setUniform4f(const std::string &name, float a, float b, float c, float d) {
    glUniform4f(this->getUniformLocation(name), a, b, c, d);
}

void Shader::setUniform3f(const std::string &name, float a, float b, float c) {
    glUniform3f(this->getUniformLocation(name), a, b, c);
}

void Shader::setUniform1f(const std::string & name, float a) {
    glUniform1f(this->getUniformLocation(name), a);
}

void Shader::setUniform1i(const std::string &name, int value) {
    glUniform1i(this->getUniformLocation(name), value);
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniform1iArr(const std::string &name, const std::vector<int> arr) {
    glUniform1iv(this->getUniformLocation(name), arr.size(), arr.data());
}

int Shader::getUniformLocation(const std::string &name) {
    if (this->uniformLocations.find(name) == this->uniformLocations.end()) {
        this->uniformLocations[name] = glGetUniformLocation(this->id, name.c_str());
    }
    return this->uniformLocations[name];
}

std::string Shader::readSourceFromFile(const std::string &filePath) {

    std::stringstream srcStream;
    std::string line;
    std::ifstream fileStream(filePath);

    while (getline(fileStream, line)) {
        srcStream << line << '\n';
    }

    return srcStream.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string &src) {

    unsigned int shaderId = glCreateShader(type);
    const auto rawSrc = src.c_str();

    glShaderSource(shaderId, 1, &rawSrc, nullptr);
    glCompileShader(shaderId);

    int compileStatus;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE) {

        int messageLength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &messageLength);
        
        auto message = std::make_unique<char[]>(messageLength);
        glGetShaderInfoLog(shaderId, messageLength, &messageLength, message.get());

        std::cout << "Failed to compile shader, OpenGL message: " << message << std::endl;
        
        glDeleteShader(shaderId);

        return 0;
    }

    return shaderId;
}

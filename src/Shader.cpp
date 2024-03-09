#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

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

void Shader::setUnifromVec4(const std::string &name, float a, float b, float c, float d) {
    glUniform4f(this->getUniformLocation(name), a, b, c, d);
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

        char* message = new char[messageLength];
        glGetShaderInfoLog(shaderId, messageLength, &messageLength, message);

        std::cout << "Failed to compile shader, OpenGL message: " << message << std::endl;
        
        glDeleteShader(shaderId);
        delete[] message;

        return 0;
    }

    return shaderId;
}

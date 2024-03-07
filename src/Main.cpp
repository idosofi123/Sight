#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <format>

static std::string readShaderFile(const std::string &filePath) {

    std::stringstream srcStream;
    std::string line;
    std::ifstream fileStream(filePath);

    while (getline(fileStream, line)) {
        srcStream << line << '\n';
    }

    return srcStream.str();
}

static unsigned int compileShader(unsigned int type, const std::string &src) {
    
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

static unsigned int createShader(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc) {

    unsigned int programId = glCreateProgram();
    unsigned int vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    unsigned int fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);
    glValidateProgram(programId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

static void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    
    std::cout << std::format("[OpenGL Error]: Type: {}, Id: {}, Message: {}", type, id, message) << std::endl;
}

int main() {

    if (!glfwInit()) {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Sight", NULL, NULL);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Sync render loop with monitor refresh rate
    glfwSwapInterval(1);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Could not initialize GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(messageCallback, 0);

    float data[8]{
        -0.5, -0.5,
        0.5, -0.5,
        0.5, 0.5,
        -0.5, 0.5
    };

    unsigned int indices[6]{
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vertexArrayObjId;
    glGenVertexArrays(1, &vertexArrayObjId);
    glBindVertexArray(vertexArrayObjId);

    unsigned int bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, data, GL_STATIC_DRAW);

    unsigned int indexBufferId;
    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertSrc = readShaderFile(R"(assets/shaders/basic.vert)");
    std::string fragSrc = readShaderFile(R"(assets/shaders/basic.frag)");

    auto shaderId = createShader(vertSrc, fragSrc);

    int colorUniLoc = glGetUniformLocation(shaderId, "u_Color");
    float currColor = 0;

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        currColor += 0.01f;
        currColor -= static_cast<int>(currColor);

        glUseProgram(shaderId);
        glUniform4f(colorUniLoc, currColor, currColor, currColor, 1);
        
        glBindVertexArray(vertexArrayObjId);

        glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glDeleteProgram(shaderId);
    glfwTerminate();
    return 0;
}
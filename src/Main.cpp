#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <format>
#include <vector>
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

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

    std::vector<float> positions{
        -0.5, -0.5,
        0.5, -0.5,
        0.5, 0.5,
        -0.5, 0.5
    };

    VertexBuffer vertexBuffer;
    vertexBuffer.setData(positions);

    VertexBufferLayout layout;
    layout.addAttribute<float>(2, false);

    VertexArray vertexArray;
    vertexArray.setBuffer(vertexBuffer, layout);

    std::vector<unsigned int> indices{
        0, 1, 2,
        2, 3, 0
    };

    IndexBuffer indexBuffer;
    indexBuffer.setData(indices);

    std::string vertSrc = Shader::readSourceFromFile(R"(assets/shaders/basic.vert)");
    std::string fragSrc = Shader::readSourceFromFile(R"(assets/shaders/basic.frag)");

    Shader basicShader(vertSrc, fragSrc);

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

        basicShader.bind();
        basicShader.setUnifromVec4("u_Color", currColor, currColor, 1, 1);
        
        vertexArray.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
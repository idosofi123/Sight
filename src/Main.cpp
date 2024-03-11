#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <unordered_map>
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"

static void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {  
    static std::unordered_map<GLenum, std::string> seveities{
        { GL_DEBUG_SEVERITY_LOW, "Low" },
        { GL_DEBUG_SEVERITY_MEDIUM, "Medium" },
        { GL_DEBUG_SEVERITY_HIGH, "High" }
    };
    std::cout << std::format("[OpenGL Error]: Severity: {}, Type: {}, Id: {}, Message: {}", seveities[severity], type, id, message) << std::endl;
}

int main() {

    if (!glfwInit()) {
        return -1;
    }

    // Enable debug context
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

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

    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(messageCallback, 0);

    // Configure blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::vector<float> positions{
        -0.5, -0.5, 0, 0,
        0.5, -0.5, 1, 0,
        0.5, 0.5, 1, 1,
        -0.5, 0.5, 0, 1
    };

    VertexBuffer vertexBuffer;
    vertexBuffer.setData(positions);

    VertexBufferLayout layout;
    layout.addAttribute<float>(2, false);
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

    Texture texture(R"(assets/textures/alert.png)");
    texture.bind();

    basicShader.bind();
    basicShader.setUnifrom1i("u_Texture", 0);

    Renderer renderer;

    float currColor = 0;

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {

        renderer.clear();

        currColor += 0.01f;
        currColor -= static_cast<int>(currColor);

        basicShader.bind();
        basicShader.setUnifrom4f("u_Color", currColor, currColor, 1, 1);

        renderer.draw(vertexArray, indexBuffer, basicShader);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
         glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
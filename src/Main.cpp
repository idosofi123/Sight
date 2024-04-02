#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Configuration.hpp"
#include "tests/TestsLibrary.hpp"
#include "tests/TestClearColor.hpp"
#include "tests/TestTexture2D.hpp"
#include "tests/Test3DCube.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

static void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {  
    static std::unordered_map<GLenum, std::string> severities{
        { GL_DEBUG_SEVERITY_LOW, "Low" },
        { GL_DEBUG_SEVERITY_MEDIUM, "Medium" },
        { GL_DEBUG_SEVERITY_HIGH, "High" }
    };
    if (severities.find(severity) != severities.end()) {
        std::cout << std::format("[OpenGL Error]: Severity: {}, Type: {}, Id: {}, Message: {}", severities[severity], type, id, message) << std::endl;
    }
}

int main() {

    if (!glfwInit()) {
        return -1;
    }

    // Enable debug context
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(Configuration::SCREEN_W, Configuration::SCREEN_H, "Sight", NULL, NULL);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    // UI setup
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    Tests::TestsLibrary testLibrary;
    testLibrary.registerTest<Tests::TestClearColor>("Clear");
    testLibrary.registerTest<Tests::TestTexture2D>("2D Texture");
    testLibrary.registerTest<Tests::Test3DCube>("3D Cube");
    
    Renderer renderer;
    testLibrary.run(window, renderer);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}
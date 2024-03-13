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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
    GLFWwindow* window = glfwCreateWindow(800, 600, "Sight", NULL, NULL);
    
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

    // UI setup
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGuiIO& uiIo = ImGui::GetIO();

    std::vector<float> positions{
        0.0f, 0.0f, 0.0f, 0.0f,
        100.0f, 0.0f, 1.0f, 0.0f,
        100.0f, 100.0f, 1.0f, 1.0f,
        0.0f, 100.0f, 0.0f, 1.0f
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

    Texture texture(R"(assets/textures/box.png)");
    texture.bind();

    basicShader.bind();
    basicShader.setUnifrom1i("u_Texture", 0);

    auto projectionMat = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    auto viewMat = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f });
    glm::vec3 translationVec{ 0.0f, 0.0f, 0.0f };

    Renderer renderer;

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {

        // Poll for and process events
        glfwPollEvents();

        renderer.clear();

        auto modelMat = glm::translate(glm::mat4(1.0f), translationVec);

        basicShader.bind();
        basicShader.setUnifromMat4f("u_MVP", projectionMat * viewMat * modelMat);

        renderer.draw(vertexArray, indexBuffer, basicShader);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Configuration");
        ImGui::Text("%.1f FPS", uiIo.Framerate);
        ImGui::SliderFloat2("Position", &translationVec.x, 0, 600);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
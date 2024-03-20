#include "TestTexture2D.hpp"
#include <imgui.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Tests {

    TestTexture2D::TestTexture2D() :
        shader(
            Shader::readSourceFromFile(R"(assets/shaders/basic.vert)"),
            Shader::readSourceFromFile(R"(assets/shaders/basic.frag)")),
        texture(R"(assets/textures/alert.png)"),
        translation(0.0f, 0.0f, 0.0f),
        projection(glm::ortho(0.0f, 800.0f, 0.0f, 600.0f)),
        view(glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f })) {
        
        this->vertexBuffer.setData<float>({
            -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f, 50.0f, 1.0f, 1.0f,
            -50.0f, 50.0f, 0.0f, 1.0f
        });

        VertexBufferLayout layout;
        layout.addAttribute<float>(2, false);
        layout.addAttribute<float>(2, false);

        this->vertexArray.setBuffer(vertexBuffer, layout);

        this->indexBuffer.setData<unsigned int>({
            0, 1, 2,
            2, 3, 0
        });

        this->texture.bind();
        this->shader.bind();
        this->shader.setUnifrom1i("u_Texture", 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    TestTexture2D::~TestTexture2D() {
        glDisable(GL_BLEND);
    }

    void TestTexture2D::update(float deltaTime) {

    }

    void TestTexture2D::render(const Renderer &renderer) {

        renderer.clear(0, 0, 0, 1);
        auto modelMat = glm::translate(glm::mat4(1.0f), this->translation);

        this->shader.bind();
        this->shader.setUnifromMat4f("u_MVP", projection * view * modelMat);

        renderer.draw(this->vertexArray, this->indexBuffer, this->shader);
    }

    void TestTexture2D::renderUI() {
        ImGui::Begin("Configuration");
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
        ImGui::SliderFloat2("Position", &this->translation.x, 0, 600);
        ImGui::End();
    }

}
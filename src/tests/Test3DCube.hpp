#pragma once
#include "Test.hpp"
#include <imgui.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Shader.hpp"
#include "../IndexBuffer.hpp"
#include "../VertexBuffer.hpp"
#include "../VertexArray.hpp"
#include "../Texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tests {

    class Test3DCube : public Test {

    private:
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        Shader shader;
        VertexArray vertexArray;
        glm::vec3 model;
        float yRotation;
        glm::vec3 view;
        glm::mat4 projection;
        Texture texture;

    public:

        Test3DCube() :
            shader(
                Shader::readSourceFromFile(R"(assets/shaders/basic.vert)"),
                Shader::readSourceFromFile(R"(assets/shaders/basic.frag)")),
            texture(R"(assets/textures/amitse.png)"),
            projection(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
            model({0.0f, 0.0f, 0.0f}),
            view({0.0f, 0.0f, -2.0f}),
            yRotation(0.0f) {

            glEnable(GL_DEPTH_TEST);

            vertexBuffer.setData<float>({
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 0.0f, 1.0f
            });

            VertexBufferLayout layout;
            layout.addAttribute<float>(3, false);
            layout.addAttribute<float>(2, false);

            vertexArray.setBuffer(vertexBuffer, layout);

            indexBuffer.setData<unsigned int>({
                0, 1, 2,
                2, 3, 0,
                4, 5, 6,
                6, 7, 4,
                0, 3, 7,
                7, 4, 0,
                1, 2, 6,
                6, 5, 1,
                0, 1, 5,
                5, 4, 0,
                2, 3, 7,
                7, 6, 2
            });

            this->texture.bind();

            this->shader.bind();
            this->shader.setUnifrom1i("u_Texture", 0);

        }
        
        ~Test3DCube() {

        }

        virtual void update(double deltaTime) override {
            yRotation += deltaTime * 15.0f;
        }

        virtual void render(const Renderer &renderer) override {
            renderer.clear(0.1, 0.25, 0.9, 1);
            
            auto modelMat = glm::translate(glm::mat4(1.0f), model);
            modelMat = glm::rotate(modelMat, glm::radians(yRotation), glm::vec3(1.0f, 1.0f, 1.0f));
            auto viewMat = glm::translate(glm::mat4(1.0f), view);

            this->shader.bind();
            this->shader.setUnifromMat4f("u_MVP", projection * viewMat * modelMat);

            renderer.draw(this->vertexArray, this->indexBuffer, this->shader);
        }

        virtual void renderUI() override {
            ImGui::Begin("Configuration");
            ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
            ImGui::SliderFloat3("Position", &model.x, -10.0f, 10.0f);
            ImGui::End();
        }
    };
}
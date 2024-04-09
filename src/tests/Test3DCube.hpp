#pragma once
#include "Test.hpp"
#include <imgui.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Shader.hpp"
#include "../IndexBuffer.hpp"
#include "../VertexBuffer.hpp"
#include "../VertexArray.hpp"
#include "../Mesh.hpp"
#include "../Texture.hpp"
#include "../Model.hpp"
#include "../Camera.hpp"
#include "../Cubemap.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace Tests {

    class Test3DCube : public Test {

    private:

        Shader shader;
        Shader skyboxShader;
        glm::vec3 model;
        Model bagModel;
        Mesh skyboxMesh;
        VertexBuffer lightVBO;
        IndexBuffer lightEBO;
        VertexArray lightVAO;
        Shader defaultShader;
        glm::vec3 lightModel;
        Cubemap cubemap;

        glm::vec3 cameraVelocity;
        float rotation;
        Camera camera;
        bool inDragMode = false;
        glm::vec4 lightColor{1.0f, 1.0f, 1.0f, 1.0f};

    public:

        Test3DCube() :
            shader(
                Shader::readSourceFromFile(R"(assets/shaders/basic.vert)"),
                Shader::readSourceFromFile(R"(assets/shaders/basic.frag)")),
            defaultShader(
                Shader::readSourceFromFile(R"(assets/shaders/light.vert)"),
                Shader::readSourceFromFile(R"(assets/shaders/light.frag)")),
            model({0.0f, 0.f, 0.0f}),
            lightModel({3.0f, 0.0f, 0.0f}),
            rotation(0.0f),
            camera({0.0f, 0.0f, 5.0f}, {0.0f, 0.0f, -1.0f}, 45.0f, 0.1f, 100.0f, Configuration::SCREEN_W, Configuration::SCREEN_H),
            cameraVelocity({0.0f, 0.0f, 0.0f}),
            bagModel(R"(assets/models/plasmaSword/scene.gltf)"),
            cubemap({
                R"(assets/textures/skybox/right.jpg)",
                R"(assets/textures/skybox/left.jpg)",
                R"(assets/textures/skybox/top.jpg)",
                R"(assets/textures/skybox/bottom.jpg)",
                R"(assets/textures/skybox/front.jpg)",
                R"(assets/textures/skybox/back.jpg)"
            }),
            skyboxMesh({
                {{-0.5f, -0.5f, -0.5f}},
                {{-0.5f, -0.5f, 0.5f}},
                {{0.5f, -0.5f, 0.5f}},
                {{0.5f, -0.5f, -0.5f}},
                {{-0.5f, 0.5f, -0.5f}},
                {{-0.5f, 0.5f, 0.5f}},
                {{0.5f, 0.5f, 0.5f}},
                {{0.5f, 0.5f, -0.5f}}
            },{
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
            }, nullptr, nullptr),
            skyboxShader(
                Shader::readSourceFromFile(R"(assets/shaders/skybox.vert)"),
                Shader::readSourceFromFile(R"(assets/shaders/skybox.frag)")) {

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);

            lightVBO.setData<float>({
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f,
                -0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, -0.5f
            });

            lightEBO.setData<unsigned int>({
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

            VertexBufferLayout defaultLayout;
            defaultLayout.addAttribute<float>(3, false);

            lightVAO.bindBuffers(lightVBO, defaultLayout, lightEBO);

            shader.bind();
            shader.setUniform4f("u_LightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
            shader.setUniform1f("u_innerConeCos", glm::cos(glm::radians(5.0f)));
            shader.setUniform1f("u_outerConeCos", glm::cos(glm::radians(10.0f)));

            defaultShader.bind();
            defaultShader.setUniform4f("u_Color", lightColor.x, lightColor.y, lightColor.z, lightColor.w);

        }
        
        ~Test3DCube() {
            glDisable(GL_DEPTH_TEST);
        }

        void handleInput(GLFWwindow* window) {

            cameraVelocity = {0.0f, 0.0f, 0.0f};

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                cameraVelocity += camera.direction;
            }

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                cameraVelocity += glm::normalize(glm::cross(Camera::UP_VECTOR, camera.direction));
            }

            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                cameraVelocity += -camera.direction;
            }

            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                cameraVelocity += glm::normalize(glm::cross(camera.direction, Camera::UP_VECTOR));
            }

            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
                cameraVelocity += Camera::UP_VECTOR;
            }

            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
                cameraVelocity += -Camera::UP_VECTOR;
            }

            if (glm::length(cameraVelocity) > 0.0f) {
                cameraVelocity = 3.0f * glm::normalize(cameraVelocity);
            }

            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

                if (!inDragMode) {
                    glfwSetCursorPos(
                        window,
                        static_cast<double>(Configuration::SCREEN_W) / 2,
                        static_cast<double>(Configuration::SCREEN_H) / 2);
                    inDragMode = true;   
                }

                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

                double mouseX, mouseY;
                glfwGetCursorPos(window, &mouseX, &mouseY);

                constexpr float SENSITIVITY = 50.0f;
                constexpr float LIMIT_OFFSET = 3.0f;

                float rotateX = (mouseX - (static_cast<float>(Configuration::SCREEN_W) / 2)) / Configuration::SCREEN_W;
                float rotateY = (mouseY - (static_cast<float>(Configuration::SCREEN_H) / 2)) / Configuration::SCREEN_H;

                glm::vec3 newDirection = glm::rotate(
                    camera.direction,
                    glm::radians(-rotateY * SENSITIVITY),
                    glm::cross(camera.direction, Camera::UP_VECTOR));

                newDirection = glm::rotate(
                    newDirection,
                    glm::radians(-rotateX * SENSITIVITY),
                    Camera::UP_VECTOR);

                if (glm::angle(Camera::UP_VECTOR, newDirection) >= glm::radians(LIMIT_OFFSET) && glm::angle(-Camera::UP_VECTOR, newDirection) >= glm::radians(LIMIT_OFFSET)) {
                    camera.direction = newDirection;
                }

                glfwSetCursorPos(
                    window,
                    static_cast<double>(Configuration::SCREEN_W) / 2,
                    static_cast<double>(Configuration::SCREEN_H) / 2);

            } else {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                inDragMode = false;
            }
        }

        virtual void update(float deltaTime) override {
            rotation += deltaTime * 30.0f;
            camera.position += deltaTime * cameraVelocity;
        }

        virtual void render(const Renderer &renderer) override {

            renderer.clear(0.027, 0.052, 0.09, 1);

            auto modelMat = glm::rotate(glm::translate(glm::mat4(1.0f), model), glm::radians(rotation), glm::vec3(1.0f, 1.0f, 1.0f));

            shader.bind();
            shader.setUniformMat4f("u_Model", modelMat);
            shader.setUniformMat4f("u_ModelTi", glm::transpose(glm::inverse(modelMat)));
            shader.setUniformMat4f("u_MVP", camera.getProjectionMatrix() * camera.getViewMatrix() * modelMat);
            shader.setUniform4f("u_LightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
            shader.setUniform3f("u_LightPosition", lightModel.x, lightModel.y, lightModel.z);
            shader.setUniform3f("u_CameraPosition", camera.position.x, camera.position.y, camera.position.z);
            shader.setUniform3f("u_SpotLightDirection", -1, 0, 0);

            bagModel.draw(renderer, shader);

            auto lightModelMat = glm::translate(glm::mat4(1.0f), lightModel);

            defaultShader.bind();
            defaultShader.setUniformMat4f("u_MVP", camera.getProjectionMatrix() * camera.getViewMatrix() * lightModelMat);
            defaultShader.setUniform4f("u_Color", lightColor.x, lightColor.y, lightColor.z, lightColor.w);

            renderer.draw(lightVAO, defaultShader);

            skyboxShader.bind();
            cubemap.bind();
            skyboxShader.setUniformMat4f("u_MVP", camera.getProjectionMatrix() * glm::mat4(glm::mat3(camera.getViewMatrix())));
            skyboxShader.setUniform1i("u_Texture", 0);

            skyboxMesh.draw(renderer, skyboxShader);
        }

        virtual void renderUI() override {
            ImGui::Begin("Configuration");
            ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
            ImGui::SliderFloat3("Position", &model.x, -10.0f, 10.0f);
            ImGui::SliderFloat3("Light Position", &lightModel.x, -10.0f, 10.0f);
            ImGui::ColorPicker4("Light Color", &lightColor.x);
            ImGui::End();
        }
    };
}
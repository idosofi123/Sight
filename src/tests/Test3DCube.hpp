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
#include "../Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace Tests {

    class Test3DCube : public Test {

    private:
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        Shader shader;
        VertexArray vertexArray;
        glm::vec3 model;
        glm::vec3 cameraVelocity;
        float rotation;
        Camera camera;
        Texture texture;
        bool inDragMode = false;

    public:

        Test3DCube() :
            shader(
                Shader::readSourceFromFile(R"(assets/shaders/basic.vert)"),
                Shader::readSourceFromFile(R"(assets/shaders/basic.frag)")),
            texture(R"(assets/textures/amitse.png)"),
            model({0.0f, 0.0f, 0.0f}),
            rotation(0.0f),
            camera({0.0f, 0.0f, 5.0f}, {0.0f, 0.0f, -1.0f}, 45.0f, 0.1f, 100.0f, Configuration::SCREEN_W, Configuration::SCREEN_H),
            cameraVelocity({0.0f, 0.0f, 0.0f}) {

            glEnable(GL_DEPTH_TEST);

            vertexBuffer.setData<float>({
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f
            });

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

            VertexBufferLayout layout;
            layout.addAttribute<float>(3, false);
            layout.addAttribute<float>(2, false);

            vertexArray.bindBuffers(vertexBuffer, layout, indexBuffer);

            this->texture.bind();

            this->shader.bind();
            this->shader.setUnifrom1i("u_Texture", 0);

        }
        
        ~Test3DCube() {

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
            rotation += deltaTime * 50.0f;
            camera.position += deltaTime * cameraVelocity;
        }

        virtual void render(const Renderer &renderer) override {

            renderer.clear(0.1, 0.25, 0.9, 1);
            
            this->vertexArray.bind();

            auto modelMat = glm::rotate(glm::translate(glm::mat4(1.0f), model), glm::radians(rotation), glm::vec3(1.0f, 1.0f, 1.0f));

            this->shader.bind();
            this->shader.setUnifromMat4f("u_MVP", camera.getCameraMatrix() * modelMat);

            renderer.draw(this->vertexArray, this->shader);
        }

        virtual void renderUI() override {
            ImGui::Begin("Configuration");
            ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
            ImGui::SliderFloat3("Position", &model.x, -10.0f, 10.0f);
            ImGui::Text("%.3f, %.3f, %.3f", camera.direction.x, camera.direction.y, camera.direction.z);
            ImGui::End();
        }
    };
}
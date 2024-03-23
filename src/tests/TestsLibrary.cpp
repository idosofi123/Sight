#include "TestsLibrary.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <algorithm>
#include "../Renderer.hpp"

namespace Tests {

    TestsLibrary::TestsLibrary() {

    }

    TestsLibrary::~TestsLibrary() {

    }

    void TestsLibrary::run(GLFWwindow* window, const Renderer &renderer) {

        float prevTime = glfwGetTime();

        while (!glfwWindowShouldClose(window)) {

            // Poll for and process events
            glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            double currTime = glfwGetTime();
            if (this->chosenTest) {
                this->chosenTest->update(currTime - prevTime);
                this->chosenTest->render(renderer);
                this->chosenTest->renderUI();
            }

            prevTime = currTime;

            ImGui::Begin("Test Library");

            for (const auto &testOption : this->tests) {

                if (ImGui::Button(testOption.first.c_str())) {

                    // Ensure cleanup executes before initiation of new test
                    this->chosenTest = nullptr;

                    this->chosenTest = testOption.second();
                }
            }

            ImGui::End();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }
    }
}
#pragma once
#include <string>
#include "../Renderer.hpp"
#include "../Configuration.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Tests {

    class Test {

    private:
        std::string label;

    public:

        Test();
        virtual ~Test();

        virtual void handleInput(GLFWwindow* window) {}
        virtual void update(float deltaTime) {}
        virtual void render(const Renderer &renderer) = 0;
        virtual void renderUI() {}
    };

}
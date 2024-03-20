#pragma once
#include "Test.hpp"
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Tests {

    class TestsLibrary {

    private:
    
        std::vector<std::pair<std::string, std::function<std::unique_ptr<Test>()>>> tests;
        std::unique_ptr<Test> chosenTest;

    public:

        TestsLibrary();
        ~TestsLibrary();
        void run(GLFWwindow* window, const Renderer &renderer);

        template <typename T>
        void registerTest(std::string name) {

            static_assert(std::is_base_of<Test, T>::value, "Given template type must be a test.");

            this->tests.push_back({ std::move(name), [](){
                return std::make_unique<T>();
            } });
        }
    };

}
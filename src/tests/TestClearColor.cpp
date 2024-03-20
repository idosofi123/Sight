#include "TestClearColor.hpp"
#include <GL/glew.h>

namespace Tests {

    TestClearColor::TestClearColor() : Test() {

    }

    TestClearColor::~TestClearColor() {

    }

    void TestClearColor::update(float deltaTime) {

    }

    void TestClearColor::render(const Renderer &renderer) {
        renderer.clear(1, 1, 1, 1);
    }

    void TestClearColor::renderUI() {

    }

}
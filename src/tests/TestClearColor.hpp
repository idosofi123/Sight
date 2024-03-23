#pragma once
#include "Test.hpp"

namespace Tests {

    class TestClearColor : public Test {

    private:


    public:
        TestClearColor();
        ~TestClearColor();

        virtual void update(double deltaTime) override;
        virtual void render(const Renderer &renderer) override;
        virtual void renderUI() override;
    };

}
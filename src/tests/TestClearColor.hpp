#pragma once
#include "Test.hpp"

namespace Tests {

    class TestClearColor : public Test {

    private:


    public:
        TestClearColor();
        ~TestClearColor();
        
        virtual void render(const Renderer &renderer) override;
        virtual void renderUI() override;
    };

}
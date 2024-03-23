#pragma once
#include <string>
#include "../Renderer.hpp"

namespace Tests {

    class Test {

    private:
        std::string label;

    public:

        Test();
        virtual ~Test();

        virtual void update(double deltaTime) {};
        virtual void render(const Renderer &renderer) = 0;
        virtual void renderUI() {};
    };

}
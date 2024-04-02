#pragma once
#include "Shader.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

class Drawable {
    
    public:
        virtual void draw(const Renderer &renderer, Shader &shader) const = 0;
};
#pragma once
#include "Test.hpp"
#include "../Shader.hpp"
#include "../IndexBuffer.hpp"
#include "../VertexBuffer.hpp"
#include "../VertexArray.hpp"
#include "../Texture2D.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Tests {

    class TestTexture2D : public Test {

    private:
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        Shader shader;
        VertexArray vertexArray;
        glm::vec3 translation;
        glm::mat4 projection;
        glm::mat4 view;
        Texture2D texture;

    public:
        TestTexture2D();
        ~TestTexture2D();

        virtual void render(const Renderer &renderer) override;
        virtual void renderUI() override;
    };

}
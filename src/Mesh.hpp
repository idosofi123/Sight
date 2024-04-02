#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Drawable.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoord;
    unsigned int textureIndex = 0;
};

class Mesh : public Drawable {

private:

    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    VertexArray vertexArray;
    std::vector<std::pair<Texture, Texture>> textures;

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::pair<Texture, Texture>> textures);
    Mesh(Mesh&&);
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) = delete;
    virtual void draw(const Renderer &renderer, Shader &shader) const override;
    ~Mesh();

    // Temporary for hardcoded initialization
    void setTextures(std::vector<std::pair<Texture, Texture>> textures);
};
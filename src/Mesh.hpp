#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Drawable.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoord;
};

class Mesh : public Drawable {

private:

    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    VertexArray vertexArray;
    std::shared_ptr<Texture> diffuseMap, specularMap;

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Texture> diffuseMap, std::shared_ptr<Texture> specularMap);
    Mesh(Mesh&&);
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) = delete;
    virtual void draw(const Renderer &renderer, Shader &shader) const override;
    ~Mesh();
};
#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include "VertexArray.hpp"
#include "NonCopyable.hpp"
#include "Texture2D.hpp"
#include "Drawable.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal = {0.0f, 0.0f, 0.0f};
    glm::vec2 textureCoord = {0.0f, 0.0f};
};

class Mesh : public Drawable, public NonCopyable<Mesh> {

private:

    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    VertexArray vertexArray;
    std::shared_ptr<Texture2D> diffuseMap, specularMap;

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Texture2D> diffuseMap, std::shared_ptr<Texture2D> specularMap);
    Mesh(Mesh&&);
    virtual void draw(const Renderer &renderer, Shader &shader) const override;
    ~Mesh();
};
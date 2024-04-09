#include "Mesh.hpp"

Mesh::Mesh(
    std::vector<Vertex> vertices,
    std::vector<unsigned int> indices,
    std::shared_ptr<Texture2D> diffuseMap,
    std::shared_ptr<Texture2D> specularMap) : diffuseMap(diffuseMap), specularMap(specularMap) {

    this->vertexBuffer.setData<Vertex>(std::move(vertices));
    this->indexBuffer.setData(std::move(indices));

    VertexBufferLayout layout;
    layout.addAttribute<float>(3, false);
    layout.addAttribute<float>(3, false);
    layout.addAttribute<float>(2, false);

    this->vertexArray.bindBuffers(this->vertexBuffer, layout, this->indexBuffer);
}

Mesh::Mesh(Mesh &&mesh) : 
    vertexBuffer(std::move(mesh.vertexBuffer)), 
    indexBuffer(std::move(mesh.indexBuffer)), 
    vertexArray(std::move(mesh.vertexArray)), 
    diffuseMap(mesh.diffuseMap),
    specularMap(mesh.specularMap) {

}

void Mesh::draw(const Renderer &renderer, Shader &shader) const {

    // TODO: Figure out a cleaner and more generalized way of handling textures of diff. types
    int initialSlot = 0;

    shader.bind();

    if (this->diffuseMap) {
        this->diffuseMap->bind(initialSlot);
        shader.setUniform1i("u_Texture", initialSlot++);
    }

    if (this->specularMap) {
        this->specularMap->bind(initialSlot);
        shader.setUniform1i("u_SpecularMap", initialSlot++);
    }

    renderer.draw(this->vertexArray, shader);
}

Mesh::~Mesh() {

}

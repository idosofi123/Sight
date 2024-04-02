#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::pair<Texture, Texture>> textures)
    : textures(std::move(textures)) {

    this->vertexBuffer.setData<Vertex>(std::move(vertices));
    this->indexBuffer.setData(std::move(indices));

    VertexBufferLayout layout;
    layout.addAttribute<float>(3, false);
    layout.addAttribute<float>(3, false);
    layout.addAttribute<float>(2, false);
    layout.addAttribute<unsigned int>(1, false);

    this->vertexArray.bindBuffers(this->vertexBuffer, layout, this->indexBuffer);

}

void Mesh::draw(const Renderer &renderer, Shader &shader) const {

    std::vector<int> textureIds(this->textures.size()), specularMapIds(this->textures.size());
    int slot = 0;

    for (size_t i = 0; i < this->textures.size(); i++) {

        this->textures[i].first.bind(slot);
        textureIds[i] = slot++;

        this->textures[i].second.bind(slot);
        specularMapIds[i] = slot++;
    }

    shader.bind();
    shader.setUniform1iArr("u_Textures", textureIds);
    shader.setUniform1iArr("u_SpecularMaps", specularMapIds);

    renderer.draw(this->vertexArray, shader);
}

Mesh::~Mesh() {

}

void Mesh::setTextures(std::vector<std::pair<Texture, Texture>> textures) {
    this->textures = std::move(textures);
}

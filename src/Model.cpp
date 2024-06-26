#include "Model.hpp"

Model::Model(const std::string& filePath) : directoryPath(filePath.substr(0, filePath.find_last_of('/') + 1)) {

    Assimp::Importer importer;
    auto scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        return;
    }

    this->processNode(scene->mRootNode, scene);
}

Model::Model(Model &&model) : meshes(std::move(model.meshes)), directoryPath(std::move(model.directoryPath)) {

}

Model::~Model() {

}

void Model::processNode(aiNode* node, const aiScene* scene) {

    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        this->meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::string diffusePath, specularPath = R"(assets/textures/defaultSpecularMap.png)";

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back({
            { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z },
            { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z },
            mesh->HasTextureCoords(0) ? glm::vec2{ mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y } : glm::vec2{0, 0}
        });
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const auto &face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {

        const auto &meshMaterial = scene->mMaterials[mesh->mMaterialIndex];

        // TODO: Generalize, as now this code assumes the material holds at most one diffuse texture and at most one specular map.
        // TODO: Maintain a singleton asset manager.

        aiString aiPath;

        meshMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);
        diffusePath.assign(aiPath.C_Str(), aiPath.length);
        diffusePath = this->directoryPath + diffusePath;

        if (meshMaterial->GetTexture(aiTextureType_SPECULAR, 0, &aiPath) == aiReturn_SUCCESS) {
            specularPath.assign(aiPath.C_Str(), aiPath.length);
            specularPath = this->directoryPath + specularPath;
        }
    }

    return Mesh(
        std::move(vertices),
        std::move(indices),
        this->loadTexture(diffusePath),
        this->loadTexture(specularPath));
}

std::shared_ptr<Texture2D> Model::loadTexture(const std::string& path) {

    if (this->textures.find(path) == this->textures.end()) {
        this->textures[path] = std::make_shared<Texture2D>(path);
    }

    return this->textures[path];
}

void Model::draw(const Renderer& renderer, Shader& shader) const {
    for (const auto &mesh : this->meshes) {
        mesh.draw(renderer, shader);
    }
}
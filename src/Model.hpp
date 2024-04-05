#pragma once
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Drawable.hpp"
#include "Texture.hpp"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model : public Drawable {

    private:

        std::vector<Mesh> meshes;
        std::string directoryPath;
        std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::shared_ptr<Texture> loadTexture(const std::string &path);

    public:
    
        Model(const std::string &filePath);
        Model(Model&&);
        Model(const Model&) = delete;
        Model& operator=(const Model&) = delete;
        Model& operator=(Model&&) = delete;
        virtual void draw(const Renderer &renderer, Shader &shader) const override;
        ~Model();
};
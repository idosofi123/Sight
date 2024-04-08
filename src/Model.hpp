#pragma once
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Drawable.hpp"
#include "Texture2D.hpp"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model : public Drawable, public NonCopyable<Model> {

    private:

        std::vector<Mesh> meshes;
        std::string directoryPath;
        std::unordered_map<std::string, std::shared_ptr<Texture2D>> textures;

        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::shared_ptr<Texture2D> loadTexture(const std::string &path);

    public:
    
        Model(const std::string &filePath);
        Model(Model&&);
        virtual void draw(const Renderer &renderer, Shader &shader) const override;
        ~Model();
};
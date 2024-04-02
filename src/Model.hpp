#pragma once
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Drawable.hpp"
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model : public Drawable {

    private:
        std::vector<Mesh> meshes;
        std::string directoryPath;
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    public:
        Model(const std::string &filePath);
        virtual void draw(const Renderer &renderer, Shader &shader) const override;
        ~Model();
};
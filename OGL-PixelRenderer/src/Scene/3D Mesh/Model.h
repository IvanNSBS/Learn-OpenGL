#pragma once

#include <vector>
#include "Mesh.h"
#include "../../ImGuiWindows/PropertyWindow/PR_PropertyDef.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../OpenGL/Shaders/ShaderProgram.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Cameras/Camera.h"

#include <unordered_map>

class Model : public PR_PropertyDef
{
public:
	Model(const char* path, const char* vert, const char* frag);
	~Model();

	void BeginProperty() override;
	void Draw(Camera* cam);

	glm::mat4* ModelMatrix();

protected:
	std::unordered_map<std::string, Material*> matMap; // map with existing materials

	ShaderProgram* _shader = nullptr;

	std::vector<Mesh*> _meshes;

	// Model Transform Data
	glm::vec3 _position = glm::vec3(0, -3.3, -8.9);
	glm::vec3 _rotation = glm::vec3(0);
	glm::vec3 _scale = glm::vec3(1);
	// Model Transform Matrix
	glm::mat4 _model;

	//Skinned Mesh Data;
	int jointCount;
	glm::mat4 globalInverseTransform = glm::mat4(1);

	// Mesh loader Helper Functions
	bool LoadFromFile(const char *path);
	void ProcessMeshNode(aiNode* node, const aiScene* scene, Mesh* parent = nullptr);
	MeshData* ProcessMeshData(aiMesh* mesh, aiNode* node, const aiScene* scene, Mesh* parent);
};


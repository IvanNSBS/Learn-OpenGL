#include "Model.h"


Model::Model(const char* path, const char* vert, const char* frag) {
	LoadFromFile(path);
	printf("Number of Meshes: %i\n", _meshes.size());
	printf("Number of Mesh[0] vertices: %i\n", _meshes[0].vertices.size());
	printf("Number of Mesh[0] indices: %i\n", _meshes[0].indices.size());
	_shader = new ShaderProgram(vert, frag);
}
Model::~Model() { }

glm::mat4* Model::ModelMatrix() {
	_model = glm::mat4(1.f);
	glm::vec3 nScale = glm::vec3(_scale.x, -_scale.y, _scale.z);
	_model = glm::scale(_model, nScale);
	_model = glm::translate(_model, _position);
	_model = glm::rotate(_model, glm::radians(_rotation.x), glm::vec3(1, 0, 0));
	_model = glm::rotate(_model, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
	_model = glm::rotate(_model, glm::radians(_rotation.z), glm::vec3(0, 0, -1));
	return &_model;
}

void Model::Draw(Camera* cam) 
{
	_shader->Bind();

	_shader->SetMat4("model", GL_FALSE, glm::value_ptr(*ModelMatrix()));
	_shader->SetMat4("view", GL_FALSE, glm::value_ptr(*cam->get_view_matrix()));
	_shader->SetMat4("projection", GL_FALSE, glm::value_ptr(*cam->get_projection_matrix()));
	_shader->SetFloat3("viewPos", cam->GetPos());

	for (auto mesh : _meshes) 
	{
		mesh.Draw();
	}
}

void Model::BeginProperty() {
	int i = 0;
	for (auto mesh : _meshes) {
		if (ImGui::CollapsingHeader(("Mesh " + std::to_string(0)).c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
			mesh.BeginProperty();
		}
	}

}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		_meshes.push_back(ProcessMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	//std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0]) {
			vertex.texUv = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
			vertex.texUv = { 0, 0 };

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	/*
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		material->Get
	}
	*/

	return Mesh(vertices, indices, new Material(_shader));
}


bool Model::LoadFromFile(const char *path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return false;
	}

	ProcessNode(scene->mRootNode, scene);

	return true;
}

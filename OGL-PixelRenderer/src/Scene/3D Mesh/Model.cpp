#include "Model.h"

#include <iostream>

Model::Model(const char* path, const char* vert, const char* frag) {
	_shader = new ShaderProgram(vert, frag);
	LoadFromFile(path);
	printf("Number of Meshes: %i\n", _meshes.size());

	for (auto mesh : _meshes) {
		mesh->PrintTree();
	}

}
Model::~Model() { 
	for (auto mesh : _meshes) {
		delete mesh;
	}
	_meshes.clear();
}

glm::mat4* Model::ModelMatrix() {
	_model = glm::mat4(1.f);
	_model = glm::scale(_model, _scale);
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
		mesh->Draw();
	}
}

void Model::BeginProperty() {
	ImGui::Text("Position: ");
	ImGui::DragFloat3("###modelPos", glm::value_ptr(_position), 0.05f);
	ImGui::Text("Rotation: ");
	ImGui::DragFloat3("###modelRot", glm::value_ptr(_rotation), 1.0f);
	ImGui::Text("Scale: ");
	ImGui::DragFloat3("###modelScale", glm::value_ptr(_scale), 0.05f);

	int i = 0;
	for (auto& material : matMap ) {
		if (ImGui::CollapsingHeader(material.second->Name().c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
			material.second->BeginProperty();
		}
		i++;
	}

}

void Model::ProcessMeshNode(aiNode* node, const aiScene* scene, Mesh* parent)
{
	if (node->mNumMeshes > 0) {
		printf("Node: %s | Child count: %i\n", node->mName.C_Str(), node->mNumChildren);
		Mesh* mesh = new Mesh(node->mName.C_Str());
		

		//add to meshes if no parent
		//else add child for tree-like structure
		if (parent == nullptr)
			_meshes.push_back(mesh);
		else
			parent->AddChild(mesh);

		// add meshesData for current mesh
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
			mesh->AddMeshData(ProcessMeshData(aiMesh, node, scene, parent));
		}
		//check if has children and process it if it has
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessMeshNode(node->mChildren[i], scene, mesh);
		}
	}

	else {
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessMeshNode(node->mChildren[i], scene);
		}
	}
}

MeshData* Model::ProcessMeshData(aiMesh* mesh, aiNode* node, const aiScene* scene, Mesh* parent)
{
	std::vector<Vertex> vertices;
	std::vector<VertexBone> bones;
	std::vector<unsigned int> indices;
	//std::vector<Texture> textures;

	aiVector3D pos, scale, axis;
	ai_real rotAngle;
	node->mTransformation.Decompose(scale, axis, rotAngle, pos);


	glm::vec3 glmpos, glmscale, glmaxis;
	glmpos = { pos.x, pos.y, pos.z };
	glmscale = { scale.x, scale.y, scale.z };
	glmaxis = { axis.x, axis.y, axis.z };

	//glmpos /= 100.0f;
	//glmscale /= 100.0f;

	//printf("Translation: (%f, %f, %f)\n", glmpos.x, glmpos.y, glmpos.z);
	//printf("Rotation: (%f, %f, %f) %f\n", glmaxis.x, glmaxis.y, glmaxis.z, rotAngle);
	//printf("Scale: (%f, %f, %f)\n\n", glmscale.x, glmscale.y, glmscale.z);

	glm::mat4 transform(1.f);
	transform = glm::translate(transform, glmpos);
	if(glmaxis.length() > 0.001f && rotAngle >= 0.001f)
		transform = glm::rotate(transform, (float)rotAngle, glmaxis);
	transform = glm::scale(transform, glmscale);

	if(parent)
		transform = parent->localTransform * transform;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0]) {
			vertex.texUv = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
			vertex.texUv = { 0, 0 };

		glm::vec4 npos = { vertex.pos.x, vertex.pos.y, vertex.pos.z, 1.0f };
		vertex.pos = transform * npos;

		glm::mat3 norm = glm::transpose(glm::inverse(transform));
		vertex.normal = norm * vertex.normal;

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	printf("number of bones: %d\n", mesh->mNumBones);
	for (unsigned int i = 0; i < mesh->mNumBones; i++){
		//mesh->mBones[i]->mOffsetMatrix

		aiVector3D pos1, scale1, axis1;
		ai_real rotAngle1;
		mesh->mBones[i]->mOffsetMatrix.Decompose(scale1, axis1, rotAngle1, pos1);


		glm::vec3 glmpos1, glmscale1, glmaxis1;
		glmpos1 = { pos1.x, pos1.y, pos1.z };
		glmscale1 = { scale1.x, scale1.y, scale1.z };
		glmaxis1 = { axis1.x, axis1.y, axis1.z };

		if(glmpos1.length() > 0)
			printf("Bone Translation: (%f, %f, %f)\n", glmpos1.x, glmpos1.y, glmpos1.z);
		if(rotAngle1 > 0.001f || rotAngle1 < -0.001f)
			printf("Bone Rotation: (%f, %f, %f) %f\n", glmaxis1.x, glmaxis1.y, glmaxis1.z, rotAngle1);
	}
	
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];

		aiString name;
		aiColor3D diffColor;
		float shininess;

		aiMat->Get(AI_MATKEY_NAME, name);
		if (matMap.find(name.C_Str()) == matMap.end()) {

			aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, diffColor);
			aiMat->Get(AI_MATKEY_SHININESS, shininess);

			Material* mat = new Material(_shader, name.C_Str(), 0.01, 0.7, 0.1f, { diffColor.r, diffColor.g, diffColor.b });
			matMap[name.C_Str()] = mat;
			return new MeshData(mesh->mName.C_Str(), transform, vertices, indices, mat);
		}
		else
			return new MeshData(mesh->mName.C_Str(), transform, vertices, indices, matMap[name.C_Str()]);
	}
	
	return new MeshData(mesh->mName.C_Str(), transform, vertices, indices, new Material(_shader, ""));
}


bool Model::LoadFromFile(const char *path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType | aiProcess_CalcTangentSpace | aiProcess_GlobalScale);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return false;
	}

	ProcessMeshNode(scene->mRootNode, scene);

	return true;
}

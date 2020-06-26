#include "Model.h"


Model::Model(const char* path, const char* vert, const char* frag) {
	ReadFromFile(path);
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
		if (ImGui::CollapsingHeader(("Mesh " + std::to_string(0)).c_str())) {
			mesh.BeginProperty();
		}
	}

}

bool Model::ReadFromFile(const char *path) {
	return false;
}

#include "Material.h"

Material::Material(ShaderProgram* sp) {
	_shader = sp;
}

Material::~Material() {
	//delete _shader;
}

void Material::Use() {
	_shader->Bind();

	//shader->SetMat4("model", GL_FALSE, glm::value_ptr(*model));
	//shader->SetMat4("view", GL_FALSE, glm::value_ptr(*view));
	//shader->SetMat4("projection", GL_FALSE, glm::value_ptr(*projection));
	//shader->SetFloat3("viewPos", viewPos);

	_shader->SetFloat3("objectColor", _color);
	_shader->SetFloat("celThreshold", _celThreshold);
	_shader->SetFloat("attenuation", _attenuation);
	_shader->SetFloat("shininess", _shininess);
}

void Material::BeginProperty() {
	ImGui::Text("Color: ");
	ImGui::ColorEdit3("###color", glm::value_ptr(_color));
	ImGui::Text("Cel Threshold");
	ImGui::DragFloat("###threshold", &_celThreshold, 0.01f, 0.0f, 1.0f);
	ImGui::Text("Cel Attenuation: ");
	ImGui::DragFloat("###attenuation", &_attenuation, 0.01f, 0.0f, 1.0f);
	ImGui::Text("Attenuation: ");
	ImGui::DragFloat("###threshold", &_shininess, 0.01f, 0.0f, 1.0f);
}
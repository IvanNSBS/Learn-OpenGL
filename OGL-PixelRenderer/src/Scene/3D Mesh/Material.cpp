#include "Material.h"

Material::Material(ShaderProgram* sp) { 
	_shader = sp;
}


Material::Material( 
	ShaderProgram* sp, 
	float thr, 
	float att, 
	float shinn, 
	glm::vec3 col) : _celThreshold(thr), _attenuation(att), _shininess(shinn), _color(col)
{
	_shader = sp;
}


Material::~Material() { }


void Material::Use() {

	_shader->SetFloat3("material.diffuseColor", _color);
	_shader->SetFloat("material.celThreshold", _celThreshold);
	_shader->SetFloat("material.celAttenuation", _attenuation);
	_shader->SetFloat("material.shininess", _shininess);
}


void Material::BeginProperty() {
	ImGui::Text("Color: ");
	ImGui::ColorEdit3("###color", glm::value_ptr(_color));
	ImGui::Text("Cel Threshold");
	ImGui::DragFloat("###threshold", &_celThreshold, 0.0025f, 0.0f, 1.0f);
	ImGui::Text("Cel Attenuation: ");
	ImGui::DragFloat("###attenuation", &_attenuation, 0.0025f, 0.0f, 1.0f);
	ImGui::Text("Shininess: ");
	ImGui::DragFloat("###shininess", &_shininess, 0.1f, 0.0f, 64.0f);
}
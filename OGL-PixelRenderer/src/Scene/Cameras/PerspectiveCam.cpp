#include "PerspectiveCam.h"

PerspectiveCam::PerspectiveCam(
	glm::vec3 from, glm::vec3 at, glm::vec3 up,
    float fov, float near, float far, PR_Viewport* viewport) :
	_fov(fov), _near(near), _far(far), _lookAt(at), _up(up)
{
	_vpRef = viewport;
	_pos = from;
	float ratio = _vpRef == nullptr ? 1.0f : _vpRef->AspectRatio();
	projection = glm::perspective(glm::radians(_fov), ratio, _near, _far);
	view = glm::lookAt(_pos, _pos + _lookAt, _up);
}

void PerspectiveCam::Update() {
	float ratio = _vpRef == nullptr ? 1.0f : _vpRef->AspectRatio();
	projection = glm::perspective(glm::radians(_fov), ratio, _near, _far);
	view = glm::lookAt(_pos, _pos + _lookAt, _up);
}

void PerspectiveCam::BeginProperty() {

	Update();

	ImGui::Text("Position: ");
	ImGui::DragFloat3("###Position", glm::value_ptr(_pos), 0.05f);
	ImGui::Text("Rotation: ");
	ImGui::DragFloat3("###Rotation", glm::value_ptr(_rotation), 0.05f);
	ImGui::Text("Field of View: ");
	ImGui::DragFloat("###FoV", &_fov, 0.05f);
}
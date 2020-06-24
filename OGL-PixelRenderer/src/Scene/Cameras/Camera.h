#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"

#include "../../ImGuiWindows/PR_Viewport.h"
#include "../../ImGuiWindows/PropertyWindow/PR_PropertyDef.h"

enum class ProjectionType { perspective, ortographic };

class Camera : public PR_PropertyDef {
public:
	//Camera(
	//	glm::vec3 from, glm::vec3 lookAt, glm::vec3 up,
	//	float fov, float near, float far, PR_Viewport *viewport) :
	//	_fov(fov), _near(near), _far(far), _lookAt(lookAt), _up(up), _pos(from)
	//{
	//	_vpRef = viewport;
	//	//_pos = { -0.5, -0.5, from.z };
	//	//glm::vec3 center = { 0.5, 0.5, 0 };
	//	//view = glm::translate(glm::mat4(1.0f), center) * 0.5f * glm::translate(glm::mat4(1.0f), -center);
	//	view = glm::lookAt(_pos, _pos + lookAt, up);
	//	projection = glm::perspective(glm::radians(_fov), _vpRef->AspectRatio(), _near, _far);
	//}

	inline glm::vec3 GetPos() const { return _pos; }
	glm::mat4* get_view_matrix() { return &view; }
	glm::mat4* get_projection_matrix() { return &projection; }

	virtual void Update() = 0;

protected:
	glm::vec3 _pos;
	glm::vec3 _rotation;

	glm::mat4 projection;
	glm::mat4 view;

	PR_Viewport* _vpRef;
};

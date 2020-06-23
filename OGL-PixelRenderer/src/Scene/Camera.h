#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"

#include "../ImGuiWindows/PR_Viewport.h"


enum class ProjectionType { perspective, ortographic };

class Camera {
public:
	glm::vec3 clearColor = glm::vec3(0.2f, 0.3f, 0.3f);

	Camera(
		glm::vec3 from, glm::vec3 lookAt, glm::vec3 up,
		float fov, float near, float far, PR_Viewport *viewport) :
		_fov(fov), _near(near), _far(far), _lookAt(lookAt), _up(up), _pos(from)
	{
		_vpRef = viewport;
		view = glm::lookAt(from, from + lookAt, up);
		projection = glm::perspective(glm::radians(_fov), _vpRef->AspectRatio(), _near, _far);
	}

	glm::vec3 get_cam_pos() const {
		return _pos;
	}

	/// <summary>
	///  must be called inside a imgui frame
	/// </summary>
	void begin_imgui() {
		view = glm::lookAt(_pos, _pos + _lookAt, _up);
		//projection = glm::perspective(glm::radians(_fov), _vpRef->AspectRatio(), _near, _far);
		projection = glm::perspective(glm::radians(_fov), 1.0f, _near, _far);

		
		if (ImGui::Begin("Camera")) {
			std::string ar = std::to_string(_vpRef->AspectRatio());
			ImGui::Text(("Aspect Ratio: " + ar).c_str());
			ImGui::ColorEdit3("Clear Color", glm::value_ptr(clearColor));
			ImGui::SliderFloat3("Position", glm::value_ptr(_pos), -20.f, 20.f);
			ImGui::SliderFloat3("Rotation", glm::value_ptr(_rotation), 0.f, 360.f);
			ImGui::SliderFloat("FoV", &_fov, 20.f, 120.f);
			ImGui::End();
		}

	}

	glm::mat4* get_view_matrix() { return &view; }
	glm::mat4* get_projection_matrix() {
		return &projection;
	}



private:
	glm::vec3 _pos;
	glm::vec3 _rotation;

	glm::vec3 _lookAt;
	glm::vec3 _up;

	float _fov;
	float _near, _far;
	PR_Viewport* _vpRef;

	glm::mat4 projection;
	glm::mat4 view;
};

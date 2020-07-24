#pragma once

#include "Camera.h"

enum class AspectType:int{Viewport = 0, Framebuffer = 1, TypeCount = 2};

class PerspectiveCam : public Camera
{
public:
	PerspectiveCam(glm::vec3 from, glm::vec3 at, glm::vec3 up, float fov, float near, float far, PR_Viewport* vp);
	void Update() override;
	void BeginProperty() override;

private:
	float _fov, _near, _far;
	glm::vec3 _lookAt, _up;
	AspectType _aspectType = AspectType::Viewport;
};


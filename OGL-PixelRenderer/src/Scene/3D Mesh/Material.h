#pragma once

#include "../../OpenGL/Shaders/ShaderProgram.h"
#include <glm/vec3.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../../ImGuiWindows/PropertyWindow/PR_PropertyDef.h"

class Material : public PR_PropertyDef
{

public:

	Material(ShaderProgram* sp, const char* name);
	Material(ShaderProgram* sp, const char*name, float thr, float att, float shinn, glm::vec3 col);
	~Material();

	void Use();
	void BeginProperty() override;
	std::string Name() { return _name;  }

private:
	ShaderProgram* _shader;
	std::string _name;

	// temp values for shader
	float _celThreshold = 0.425f;
	float _attenuation = 0.750f;
	float _shininess = 0.1f;
	glm::vec3 _color{ 0.113f, 0.25f, 0.29f };
};


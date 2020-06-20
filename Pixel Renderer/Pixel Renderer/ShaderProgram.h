#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>

class ShaderProgram {

private:
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

public:

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetFloat3(const std::string& name, glm::vec3 value) const;
	void SetMat4(const std::string& name, GLboolean transpose, GLfloat* val) const;
	void Bind();

	std::string ReadFromFile(const char* path);

	ShaderProgram(const char* vertexPath, const char* fragPath);
	~ShaderProgram();


};

#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <glad/glad.h>

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texUv;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	
	Mesh(const std::vector<Vertex> &verts, const std::vector<GLuint> &idxs, const std::vector<Texture> &texs);
	void Draw();

private:
	GLuint _VAO, _VBO, _EBO;
	void SetupMesh();
};


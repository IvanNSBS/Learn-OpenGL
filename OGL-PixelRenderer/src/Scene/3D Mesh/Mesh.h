#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <glad/glad.h>

#include "Material.h"
#include "../../ImGuiWindows/PropertyWindow/PR_PropertyDef.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texUv;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh : public PR_PropertyDef
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	
	Material* material = nullptr;

	Mesh(const std::vector<Vertex>& verts, const std::vector<GLuint>& idxs, const std::vector<Texture>& texs);
	Mesh(const std::vector<Vertex>& verts, const  std::vector<GLuint>& idxs, Material* mat);
	Mesh(const std::vector<Vertex>& verts, const  std::vector<GLuint>& idxs);
	~Mesh();

	void SetMaterial(Material* mat);
	void Draw();

	void BeginProperty() override;

private:
	GLuint _VAO, _VBO, _EBO;
	void SetupMesh();
};

